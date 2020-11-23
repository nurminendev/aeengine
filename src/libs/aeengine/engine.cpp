/*
 *  AE Engine
 *
 *  Copyright (C) 2003 Riku "Rakkis" Nurminen
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <aedefs.h>
#include <aeengine/camera.h>
#include <aeengine/engine.h>
#include <aeengine/event.h>
#include <aeengine/frustumculler.h>
#ifdef WIN32
#include <aeengine/win32/glproc.h>
#endif
#include <aegeom/object.h>
#include <aereg/registry.h>
#include <aeutil/util.h>

aeEngine::aeEngine(aeRegistry *aeReg, int width, int height, int vidflags)
{
	AECF_CNAME("aeEngine")
	aereg = aeReg;
	camera = NULL;
	frustumCuller = new aeFrustumCuller();
	screen = NULL;
	done = false;
	isactive = false;
	screenwidth = width;
	screenheight = height;
	videoflags = vidflags;
	EventHandlerCallback = NULL;
	HaveEvHandlerCallback = false;
	eflags = new aeEngineflags;
	eflags->hasMultitexture = false;
	eflags->doMultipass = false;
}

aeEngine::~aeEngine()
{
	if(camera)
		delete camera;
	if(frustumCuller)
		delete frustumCuller;
	if(eflags)
		delete eflags;

	SDL_Quit();
}

void aeEngine::InitGL()
{
    /* set the background black */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* enable smooth shading */
    glShadeModel(GL_SMOOTH);

    /* depth buffer setup */
	glClearDepth(1.0f);

    /* enables depth testing */
    glEnable(GL_DEPTH_TEST);

	float fogcolor[3] = { 0.2f, 0.2f, 0.2f };

	glEnable(GL_FOG);
	glFogf(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.004f);
	glFogf(GL_FOG_START, 130.0f);
	glFogf(GL_FOG_END, 500.0f);
	glFogfv(GL_FOG_COLOR, fogcolor);

    /* the type of depth test to do */
	glDepthFunc(GL_LEQUAL);

    /* really nice perspective calculations */
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

bool aeEngine::OpenApplication()
{
	int dbuf, texunits;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
	    Report(0, "Failed to initialize video: %s\n", SDL_GetError());
	    return false;
	}

	const SDL_VideoInfo *vidinfo = SDL_GetVideoInfo();
	if(vidinfo == NULL) {
		Report(0, "Failed to fetch video info\n");
		return false;
	}

	// default video flags (opengl, hwpalette (?), enable window resizing)
	videoflags |= SDL_OPENGL | SDL_HWPALETTE | SDL_RESIZABLE;

	// check if it's possible to create hardware surfaces
    if(vidinfo->hw_available) {
		videoflags |= SDL_HWSURFACE;
	} else {
		videoflags |= SDL_SWSURFACE;
	}

	// check if hardware blits can be done
    if(vidinfo->blit_hw) {
		videoflags |= SDL_HWACCEL;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	screenbpp = vidinfo->vfmt->BitsPerPixel;

    screen = SDL_SetVideoMode(screenwidth, screenheight, screenbpp, videoflags);
    if(!screen) {
		Report(0, "Failed to set video mode %dx%d@%dbpp: %s\n", screenwidth, screenheight, screenbpp, SDL_GetError());
		return false;
	}

	// check if we have doublebuffering
	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &dbuf);
	if(dbuf == 0) {
		Report(1, "Could not enable doublebuffering\n");
	}

	// Init OpenGL
    InitGL();
	// Init the viewing frustrum
    ResizeWindow(screenwidth, screenheight);

	Report(0, "%s / %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	Report(0, "OpenGL version: %s\n", glGetString(GL_VERSION));
	Report(0, "\n");
	if(DEBUG) {
		Report(0, "Debug mode is on\n");
		Report(0, "\n");
	}
	Report(0, "Starting in %dx%d %dbpp\n", screenwidth, screenheight, screenbpp);

	// Check for multitexturing extension
	if(aeUtil::InStr("GL_ARB_multitexture", (char *)glGetString(GL_EXTENSIONS))) {
		// Multitexturing supported
		eflags->hasMultitexture = true;
#ifdef WIN32
		glProc::Init();
#endif
	} else {
		// Multitexture not supported, use multipass multitexturing by default
		eflags->hasMultitexture = false;
		eflags->doMultipass = true;
	}

	glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &texunits);
	eflags->texUnits = texunits;
	Report(1, "Number of texture units: %d\n", texunits);
	if(eflags->hasMultitexture)
		Report(0, "Multitexturing is supported\n");
	else
		Report(0, "Multitexturing is not supported. Using multipass multitexturing\n");

	isactive = true;

	//SDL_WM_GrabInput(SDL_GRAB_ON);
	//SDL_ShowCursor(SDL_DISABLE);

	return true;
}

bool aeEngine::ResizeWindow(int new_width, int new_height)
{
    GLfloat ratio;

    if(new_height == 0) {
		new_height = 1;
	}

    ratio = (GLfloat)new_width / (GLfloat)new_height;

    /* setup viewport */
    glViewport(0, 0, (GLsizei)new_width, (GLsizei)new_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, ratio, 0.1f, 4000.0f);

    glMatrixMode(GL_MODELVIEW);

    /* reset the view */
    glLoadIdentity();

    return true;
}

void aeEngine::PrepareRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void aeEngine::Render()
{
	if(camera != NULL) {
		camera->Look();
	}

	frustumCuller->ExtractFrustum();

	for(unsigned int i = 0; i < aereg->GetObjectCount(); i++) {
		aeObject *obj = aereg->FindObject(i);
		if(obj != NULL) {
			if(frustumCuller->SphereInFrustum(obj->GetOrigin(), obj->GetBoundingSphereRadius())) {
				obj->Draw(eflags);
			}
		}
	}
}

void aeEngine::FinishRender()
{
	glFlush();

	SDL_GL_SwapBuffers();
}

bool aeEngine::DefaultRunLoop()
{
    while(!done) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_ACTIVEEVENT:
			    if(event.active.gain == 0) {
					isactive = false;
				} else {
					isactive = true;
				}
			    break;
			case SDL_VIDEORESIZE:
			    screen = SDL_SetVideoMode(event.resize.w, event.resize.h, screenbpp, videoflags);
			    if(!screen) {
					Report(1, "Couldn't resize the screen: %s\n", SDL_GetError());
				    return false;
				}
				screenwidth = event.resize.w;
				screenheight = event.resize.h;
			    ResizeWindow(event.resize.w, event.resize.h);
			    break;
			default:
			    break;
			}
			if(HaveEvHandlerCallback) {
				aeEvent ev;
				BuildEventStruct(&event, &ev);
				(*EventHandlerCallback)(ev);
			}
		}
		if(camera != NULL) {
			camera->Update();
		}
		if(HaveEvHandlerCallback) {
			aeEvent ev;
			ev.type = aeevBroadcast;
			ev.cmd.code = aecmdPreFrame;
			(*EventHandlerCallback)(ev);
		}
		PrepareRender();
		if(HaveEvHandlerCallback) {
			aeEvent ev;
			ev.type = aeevBroadcast;
			ev.cmd.code = aecmdProcessFrame;
			(*EventHandlerCallback)(ev);
		}
		FinishRender();
		if(HaveEvHandlerCallback) {
			aeEvent ev;
			ev.type = aeevBroadcast;
			ev.cmd.code = aecmdPostFrame;
			(*EventHandlerCallback)(ev);
		}
	}

	return true;
}

void aeEngine::AddObject(aeObject *obj)
{
	aereg->PushObjectToPool(obj);
}

void aeEngine::RegisterEventHandler(aeEventHandlerCallback evhandlerfunc)
{
	EventHandlerCallback = evhandlerfunc;
	HaveEvHandlerCallback = true;
}

void aeEngine::AttachCamera(aeCamera *cam)
{
	camera = cam;
}

void aeEngine::BuildEventStruct(SDL_Event *sdlev, aeEvent *ev)
{
	switch(sdlev->type) {
	case SDL_ACTIVEEVENT:
		ev->type = aeevActiveEvent;
		ev->active.type = aeevActiveEvent;
		if(sdlev->active.gain == 0) {
			ev->active.gain = 0;
		} else {
			ev->active.gain = 1;
		}
		if(sdlev->active.state == SDL_APPMOUSEFOCUS) {
			ev->active.state = aeAppMouseFocus;
		} else if(sdlev->active.state == SDL_APPINPUTFOCUS) {
			ev->active.state = aeAppInputFocus;
		} else if(sdlev->active.state == SDL_APPACTIVE) {
			ev->active.state = aeAppActive;
		}
		break;
	case SDL_KEYDOWN:
		ev->type = aeevKeyDown;
		ev->key.type = aeevKeyDown;
		ev->key.state = aePressed;
		ev->key.keysym.scancode = sdlev->key.keysym.scancode;
		ev->key.keysym.sym = (aeKey)sdlev->key.keysym.sym;
		ev->key.keysym.mod = sdlev->key.keysym.mod;
		ev->key.keysym.unicode = sdlev->key.keysym.unicode;
		break;
	case SDL_KEYUP:
		ev->type = aeevKeyUp;
		ev->key.type = aeevKeyUp;
		ev->key.state = aeReleased;
		ev->key.keysym.scancode = sdlev->key.keysym.scancode;
		ev->key.keysym.sym = (aeKey)sdlev->key.keysym.sym;
		ev->key.keysym.mod = sdlev->key.keysym.mod;
		ev->key.keysym.unicode = sdlev->key.keysym.unicode;
		break;
	case SDL_MOUSEMOTION:
		ev->type = aeevMouseMotion;
		ev->motion.type = aeevMouseMotion;
		if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) {
			ev->motion.state = aeLeftPressed;
		} else if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2)) {
			ev->motion.state = aeMiddlePressed;
		} else if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3)) {
			ev->motion.state = aeRightPressed;
		} else {
			ev->motion.state = aeNonePressed;
		}
		ev->motion.x = sdlev->motion.x;
		ev->motion.y = sdlev->motion.y;
		ev->motion.xrel = sdlev->motion.xrel;
		ev->motion.yrel = sdlev->motion.yrel;
		break;
	case SDL_MOUSEBUTTONDOWN:
		ev->type = aeevMouseButtonDown;
		ev->button.button = (aeMouseButton)sdlev->button.button;
		ev->button.state = aePressed;
		ev->button.x = sdlev->button.x;
		ev->button.y = sdlev->button.y;
		break;
	case SDL_MOUSEBUTTONUP:
		ev->type = aeevMouseButtonUp;
		break;
	case SDL_QUIT:
		ev->type = aeevQuit;
		break;
	default:
		break;
	}
	return;
}

aeObject *aeEngine::FindObject(unsigned int objnum)
{
	return aereg->FindObject(objnum);
}

aeObject *aeEngine::FindObjectByName(char *objstr)
{
	return aereg->FindObjectByName(objstr);
}

unsigned int aeEngine::GetObjectCount()
{
	return aereg->GetObjectCount();
}

aeTexture *aeEngine::FindTexture(unsigned int texnum)
{
	return aereg->FindTexture(texnum);
}

aeTexture *aeEngine::FindTextureByName(char *texstr)
{
	return aereg->FindTextureByName(texstr);
}

unsigned int aeEngine::GetTextureCount()
{
	return aereg->GetTextureCount();
}

void aeEngine::TempQuit()
{
	done = true;
}
