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

#ifndef __AEPLUGIN_AETERRMAN_TERRMAN_H__
#define __AEPLUGIN_AETERRMAN_TERRMAN_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aegeom/triangle.h>
#include <aegfx/texture.h>
#include <aeplugin/plugin.h>
#include <aereg/registry.h>

/** 
 * Interface to the terrain plugin.
 */
class aeTerrMan: public aePlugin {
	AECF_CNDEF

 private:
	aeRegistry *aereg;
	int map_size;
	int step_size;
	float height_ratio;
	unsigned char *heightmapdata;

	aeTriangle *terrdata;

	int Height(int x, int y);
	void BuildHeightMapVertices();

 public:
	aeTerrMan(aeRegistry *aeReg);
	~aeTerrMan();

	/** 
	 * Get the terrain object.
	 * You can then add the object to the engine using aeEngine::AddObject().
	 * 
	 * 
	 * @return The terrain object (as aeTriangle).
	 */
	virtual aeTriangle *GetObject() const { return terrdata; }

	/** 
	 * Set the terrain's origin.
	 * 
	 * @param x X origin.
	 * @param y Y origin.
	 * @param z Z origin.
	 */
	virtual void SetOrigin(float x, float y, float z);

	/** 
	 * Set the terrain's origin.
	 * 
	 * @param aeVector3 Vector specifying the origin.
	 */
	virtual void SetOrigin(aeVector3);

	/** 
	 * Set a material for the terrain.
	 * 
	 * @param aeMaterial * The material.
	 */
	virtual void SetMaterial(aeMaterial *);

	/** 
	 * Load a heightmap to generate terrain from.
	 * 
	 * @param filename Path to a raw filename containing heightmap data.
	 * 
	 * @return true if the heightmap was loaded succesfully.
	 */
	virtual bool LoadHeightMap(char *filename);
};

#endif // __AEPLUGIN_AETERRMAN_TERRMAN_H__
