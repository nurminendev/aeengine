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

#ifndef __AELIB_AEENGINE_ENGINE_H__
#define __AELIB_AEENGINE_ENGINE_H__

#include <aedefs.h>
#include <aeengine/camera.h>
#include <aeengine/eflags.h>
#include <aeengine/event.h>
#include <aeengine/frustumculler.h>
#include <aegeom/object.h>
#include <aegfx/texture.h>
#include <aereg/base.h>
#include <aereg/registry.h>

class aeCamera;
class aeRegistry;

/** 
 * Interface to the engine.
 * This is the main interface to the AE 3D engine.
 * 
 */

class aeEngine: public aeBase {
	AECF_CNDEF

 private:
	aeRegistry *aereg;
	aeCamera *camera;
	aeFrustumCuller *frustumCuller;
	SDL_Surface *screen;
	SDL_Event event;
	int screenwidth;
	int screenheight;
	int screenbpp;
	int videoflags;
	bool (*EventHandlerCallback)(aeEvent &);
	bool HaveEvHandlerCallback;
	bool HasMultitext;
	bool DoFakeMultitext;
	bool done;
	bool isactive;
	aeEngineflags *eflags;

	void PrepareRender();
	void FinishRender();
	void BuildEventStruct(SDL_Event *, aeEvent *);

 public:
	aeEngine(aeRegistry *aeReg, int width, int height, int vidflags);
	~aeEngine();

	/// Global engine pointer.
	static aeEngine *self_ptr;

	/** 
	 * Initialize OpenGL.
	 * This is called automagically in OpenApplication().
	 * 
	 * 
	 * @return True if OpenGL could be initialized, and false on error.
	 */
	void InitGL();

	/** 
	 * Initialize and open a window.
	 * 
	 * 
	 * @return True if window was created succesfully, false if not.
	 */
	bool OpenApplication();

	/** 
	 * Get the screen width.
	 * 
	 * 
	 * @return The screen width.
	 */
	int GetScreenWidth() const { return screenwidth; }

	/** 
	 * Get the screen height.
	 * 
	 * 
	 * @return The screen height.
	 */
	int GetScreenHeight() const { return screenheight; }

	/** 
	 * Get the camera.
	 * You must call AttachCamera() first to attach a camera.
	 * 
	 * 
	 * @return The camera object.
	 */
	aeCamera *GetCamera() const { return camera; }

	/** 
	 * Resize the window. This should be called upon aeevResize event to resize the window.
	 * 
	 * @param new_width New window width.
	 * @param new_height New window height.
	 * 
	 * @return True if the window was resized succesfully, false if not.
	 */
	bool ResizeWindow(int new_width, int new_height);

	/** 
	 * Render the screen.
	 * You must call this upon aeevProcessFrame to get anything drawn on the screen.
	 * 
	 */
	void Render();

	/** 
	 * Enter the default runloop.
	 * Usually you call this after all other initialization to enter the default runloop.
	 * 
	 * 
	 * @return True if the runloop was exited normally, false if not.
	 */
	bool DefaultRunLoop();

	/** 
	 * Add an object to the engine.
	 * You should only use this when you create your own geometry with
	 * e.g. aePolygon or aeTriangle. You do not need to add geometry loaded with e.g. the model loader
	 * plugin or the terrain plugin because the plugin will take care of that.
	 * 
	 * @param aeObject * The object to add.
	 * @sa aeLine, aePolygon, aeTriangle, aeQuad
	 */
	void AddObject(aeObject *);

	/** 
	 * Register a event handler callback function.
	 * 
	 * @param aeEventHandlerCallback Static event handler callback function.
	 */
	void RegisterEventHandler(aeEventHandlerCallback);

	/** 
	 * Attach a camera to the engine.
	 * 
	 * @param aeCamera * A camera object.
	 */
	void AttachCamera(aeCamera *);

	/** 
	 * Toggle fullscreen on/off.
	 * 
	 */
	void ToggleFullScreen();

	/** 
	 * Find object by ID.
	 * This is only a wrapper around aeRegistry::FindObject().
	 * 
	 * @param int Object ID to query.
	 * 
	 * @return The object, or NULL if it's not found.
	 */
	aeObject *FindObject(unsigned int);

	/** 
	 * Find object by name.
	 * This is only a wrapper around aeRegistry::FindObjectByName().
	 * 
	 * @param char * Object name.
	 * 
	 * @return The object, or NULL if it's not found.
	 */
	aeObject *FindObjectByName(char *);

	/** 
	 * Get the number of objects in the engine.
	 * This is only a wrapper around aeRegistry::NumObjects().
	 * 
	 * 
	 * @return The number of objects.
	 */
	unsigned int GetObjectCount();

	/** 
	 * Find texture by ID.
	 * This is only a wrapper around aeRegistry::FindTexture().
	 * 
	 * @param int Texture ID to query.
	 * 
	 * @return The texture object, or NULL if it's not found.
	 */
	aeTexture *FindTexture(unsigned int);

	/** 
	 * Find texture by name.
	 * This is only a wrapper around aeRegistry::FindTextureByName().
	 * 
	 * @param char * Texture name.
	 * 
	 * @return The texture object, or NULL if it's not found.
	 */
	aeTexture *FindTextureByName(char *);

	/** 
	 * Get the number of textures in the engine.
	 * This is only a wrapper around aeRegistry::NumTextures().
	 * 
	 * 
	 * @return The number of textures.
	 */
	unsigned int GetTextureCount();

	void TempQuit();
};

#endif // __AELIB_AEENGINE_ENGINE_H__
