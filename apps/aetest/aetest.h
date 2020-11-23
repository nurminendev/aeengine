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

#ifndef __AETEST_AETEST_H__
#define __AETEST_AETEST_H__

#include <aeengine/camera.h>
#include <aeengine/engine.h>
#include <aeengine/event.h>
#include <aegeom/model.h>
#include <aemdlldr/mdlldr.h>
#include <aereg/registry.h>
#include <aesys/system.h>
#include <aeterrman/terrman.h>
#include <aetxtldr/txtldr.h>

class aeTest {
 private:
	aeRegistry *aereg;
	aeSystem *sys;
	aeEngine *engine;
	aeCamera *camera;
	aeModelLoader *mdlldr;
	aeTerrMan *terrman;
	aeTextureLoader *txtldr;
	float waterheight;
	bool waterdir;

	void PreFrame();
	void DoFrame();
	bool EventHandler(aeEvent &);
	static bool aeTestEventHandler(aeEvent &);
	void LoadTerrain();
	void LoadOgro();
	void LoadWater();

 public:
	aeTest(aeRegistry *aeReg);
	~aeTest();

	bool Initialize();
	void Start();
};

#endif // __AETEST_AETEST_H__
