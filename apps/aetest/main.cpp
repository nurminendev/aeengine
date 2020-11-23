/*
 *  AE test application
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

#include <aedefs.h>
#include <aeengine/camera.h>
#include <aeengine/engine.h>
#include <aeengine/event.h>
#include <aegeom/line.h>
#include <aegeom/model.h>
#include <aegeom/polygon.h>
#include <aegeom/quad.h>
#include <aegeom/vector3.h>
#include <aegfx/color3.h>
#include <aegfx/texture.h>
#include <aegfx/material.h>
#include <aemdlldr/mdlldr.h>
#include <aemm/memorymanager.h>
#include <aereg/registry.h>
#include <aesys/system.h>
#include <aeterrman/terrman.h>
#include <aetxtldr/txtldr.h>
#include <aeutil/util.h>

#include "aetest.h"

AE_APPLICATION

// Global pointer to aeTest
aeTest *aetest;

aeTest::aeTest(aeRegistry *aeReg)
{
	aereg = aeReg;
	waterheight = -130.0;
	waterdir = true;
}

aeTest::~aeTest()
{
}

void aeTest::PreFrame()
{
	// Update water animation
	if(waterheight > -128.0)
		waterdir = false;
	else if(waterheight < -130.0)
		waterdir = true;

	if(waterdir)
		waterheight += 0.01f;
	else
		waterheight -= 0.01f;
}

void aeTest::DoFrame()
{
	// Set the window caption to read our current fps.
	sys->SetWindowCaption("AETest", "FPS: %.2f", camera->GetFPS());

	// Find the water textured plate
	aeObject *wplate = engine->FindObjectByName("waterplate");
	if(wplate) {
		wplate->SetOrigin(aeVector3(wplate->GetOrigin().x, waterheight, wplate->GetOrigin().z));
	}

	// Render the screen
	engine->Render();
}

bool aeTest::EventHandler(aeEvent &ev)
{
	if(ev.type == aeevBroadcast && ev.cmd.code == aecmdPreFrame) {
		PreFrame();
		return true;
	} else if(ev.type == aeevBroadcast && ev.cmd.code == aecmdProcessFrame) {
		DoFrame();
		return true;
	}
	if(ev.type == aeevKeyDown) {
		switch(ev.key.keysym.sym) {
		case AEKEY_ESCAPE:
			engine->TempQuit();
			break;
		case AEKEY_UP:
		case AEKEY_e:
			camera->upPressed = true;
			break;
		case AEKEY_DOWN:
		case AEKEY_d:
			camera->downPressed = true;
			break;
		case AEKEY_RIGHT:
		case AEKEY_f:
			camera->rightPressed = true;
			break;
		case AEKEY_LEFT:
		case AEKEY_s:
			camera->leftPressed = true;
			break;
		default:
			break;
		}
		return true;
	} else if(ev.type == aeevKeyUp) {
		switch(ev.key.keysym.sym) {
		case AEKEY_UP:
		case AEKEY_e:
			camera->upPressed = false;
			break;
		case AEKEY_DOWN:
		case AEKEY_d:
			camera->downPressed = false;
			break;
		case AEKEY_RIGHT:
		case AEKEY_f:
			camera->rightPressed = false;
			break;
		case AEKEY_LEFT:
		case AEKEY_s:
			camera->leftPressed = false;
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}

bool aeTest::aeTestEventHandler(aeEvent &ev)
{
	return aetest->EventHandler(ev);
}

bool aeTest::Initialize()
{
	// Check for command line help
	if(aereg->CmdLineHelp()) {
		aereg->Help();
		return false;
	}

	// Find the system and engine pointers from the global registry
	sys = aereg->GetSystem();
	engine = aereg->GetEngine();

	// Create the model loader plugin and verify it's valid
	mdlldr = AE_GET_PLUGIN(aereg, aeModelLoader);
	if(mdlldr == NULL) {
		aeUtil::Report("aetest.Initialize", "Couldn't get the model loader plugin\n");
		return false;
	}

	// Create the terrain plugin and verify it's valid
	terrman = AE_GET_PLUGIN(aereg, aeTerrMan);
	if(terrman == NULL) {
		aeUtil::Report("aetest.Initialize", "Couldn't get the terrman plugin\n");
		return false;
	}

	// Create the texture loader plugin and verify it's valid
	txtldr = AE_GET_PLUGIN(aereg, aeTextureLoader);
	if(txtldr == NULL) {
		aeUtil::Report("aetest.Initialize", "Couldn't get the texture loader plugin\n");
		return false;
	}

	// Register our event handler callback
	engine->RegisterEventHandler(aeTestEventHandler);

	// Initialize and open a window
	if(!engine->OpenApplication()) {
		return false;
	}

	// Create a camera
	camera = new aeCamera();
	// Position the camera (given camera position, where camera is looking at, and the
	// camera "up" vector)
	aeVector3 campos(0.0, 2.5, 6);
	aeVector3 camview(0.0, 2.5, 0.0);
	aeVector3 camupvec(0.0, 1.0, 0.0);
	camera->PositionCamera(campos, camview, camupvec);

	// Attach the camera to the engine
	engine->AttachCamera(camera);

	// Create a green grid
	aeLine *grid = new aeLine("line1");
	grid->SetColor(0.0f, 1.0f, 0.0f);
	grid->SetOrigin(aeVector3(0.0, 0.0, 0.0));
	for(float i = -50; i <= 50; i += 1) {
		grid->AddVertex(aeVector3(-50, 0, i));
		grid->AddVertex(aeVector3(50, 0, i));
		grid->AddVertex(aeVector3(i, 0, -50));
		grid->AddVertex(aeVector3(i, 0, 50));
	}

	// Add the grid to the engine
	engine->AddObject(grid);

	// Load two textures for multitextured quad
	aeTexture *smile = txtldr->LoadTexture("smiletex", "data/smile.tga");
	smile->SetTexMode(REPLACE);
	aeTexture *chess = txtldr->LoadTexture("chesstex", "data/chess.bmp");
	chess->SetTexMode(MODULATE);
	// Create a material from the two textures
	aeMaterial *quadmat = new aeMaterial("q_mat", smile, chess);

	// Create a quad
	aeQuad *quad = new aeQuad("quad1");
	// Set the (multitextured) material on the quad
	quad->SetMaterial(quadmat);
	// Set the quad to be transparent
	quad->SetTransparent(true);
	quad->SetTexCoord(0.0, 0.0);
	quad->AddVertex(aeVector3(0.0, 1.0, 0.0));
	quad->SetTexCoord(1.0, 0.0);
	quad->AddVertex(aeVector3(5.0, 1.0, 0.0));
	quad->SetTexCoord(1.0, 1.0);
	quad->AddVertex(aeVector3(5.0, 6.0, 0.0));
	quad->SetTexCoord(0.0, 1.0);
	quad->AddVertex(aeVector3(0.0, 6.0, 0.0));

	// Add the quad to the engine
	engine->AddObject(quad);

	// Create a terrain
	LoadTerrain();

	// Load a "ogro" model
	LoadOgro();

	// Load water
	LoadWater();

	return true;
}

void aeTest::LoadTerrain()
{
	// Load a texture for a terrain
	aeTexture *terrtxt = txtldr->LoadTexture("terrain1", "data/sand.bmp");
	aeMaterial *terrmat = new aeMaterial("terrain_mat", terrtxt);

	// Create the terrain.
	terrman->LoadHeightMap("data/Terrain2.raw");
	terrman->SetOrigin(aeVector3(-60.0, -230.0, 10.0));
	terrman->SetMaterial(terrmat);
	// Add the terrain to the engine
	engine->AddObject(terrman->GetObject());
}

void aeTest::LoadOgro()
{
	// Load a texture and material for the ogro
	aeTexture *ogrobase = txtldr->LoadTexture("ogrobase", "data/models/Ogrobase.pcx");
	aeMaterial *ogromat = new aeMaterial("ogro_mat", ogrobase);
	// Load the ogro model
	aeModel *ogro = mdlldr->LoadModel("ogro", "data/models/Tris.md2", ogromat);
	ogro->SetOrigin(aeVector3(380.0, -120.0, 505.0));
	// Set the ogro's animation
	ogro->SetAnimation(0, 40, 0.05f);

	// Load a texture and material for the weapon
	aeTexture *weapbase = txtldr->LoadTexture("weapbase", "data/models/Weapon.pcx");
	aeMaterial *weapmat = new aeMaterial("weapon_mat", weapbase);
	// Load the weapon model
	aeModel *weapon = mdlldr->LoadModel("weapon", "data/models/Weapon.md2", weapmat);
	weapon->SetOrigin(aeVector3(380.0, -120.0, 505.0));
	// Set the weapon's animation
	weapon->SetAnimation(0, 40, 0.05f);
}

void aeTest::LoadWater()
{
	aeTexture *water = txtldr->LoadTexture("water", "data/water2.tga");
	aeMaterial *watermat = new aeMaterial("water_mat", water);
	aePolygon *waterplate = new aePolygon("waterplate");
	waterplate->SetOrigin(aeVector3(512.0, -125.0, 512.0));
	waterplate->SetTransparent(true);
	waterplate->SetMaterial(watermat);
	waterplate->SetTexCoord(0.0, 0.0);
	waterplate->AddVertex(aeVector3(-512.0, 0.0, -512.0));
	waterplate->SetTexCoord(15.0, 0.0);
	waterplate->AddVertex(aeVector3(512.0, 0.0, -512.0));
	waterplate->SetTexCoord(15.0, 15.0);
	waterplate->AddVertex(aeVector3(512.0, 0.0, 512.0));
	waterplate->SetTexCoord(0.0, 15.0);
	waterplate->AddVertex(aeVector3(-512.0, 0.0, 512.0));

	engine->AddObject(waterplate);
}

void aeTest::Start()
{
	// Go to default runloop
	engine->DefaultRunLoop();
}

int main(int argc, char *argv[])
{
	// Create the global registry
	aeRegistry *aereg = new aeRegistry(argc, argv);

	// Create our app instance
	aetest = new aeTest(aereg);

	if(aetest->Initialize()) {
		aetest->Start();
	}

	// Delete our app instance
	delete aetest;
	// Delete the global registry. This deletes all subsystems too.
	delete aereg;

    return 0;
}
