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

#include <aedefs.h>
#include <aegeom/triangle.h>
#include <aegfx/color3.h>
#include <aegfx/material.h>
#include <aeplugin/plugin.h>
#include <aereg/registry.h>
#include <aeterrman/terrman.h>
#include <aeutil/util.h>

aeTerrMan::aeTerrMan(aeRegistry *aeReg)
{
	AECF_CNAME("aeTerrMan")
	myID = AE_PLUGIN_aeTerrMan;

	aereg = aeReg;
	map_size = 1024;
	step_size = 32;
	height_ratio = 1.5f;
	heightmapdata = NULL;

	terrdata = new aeTriangle();
	terrdata->SetMode(TRIANGLES_STRIP);
}

aeTerrMan::~aeTerrMan()
{
	if(heightmapdata != NULL) {
		delete heightmapdata;
	}
}

void aeTerrMan::BuildHeightMapVertices()
{
	int X = 0,  Y = 0;
	int x, y, z;
	bool bSwitchSides = false;

	for(X = 0; X <= map_size; X += step_size) {
		if(bSwitchSides) {
			for(Y = map_size; Y >= 0; Y -= step_size) {
				x = X;
				y = Height(X, Y);
				z = Y;

				terrdata->SetTexCoord((float)x / (float)map_size, (float)z / (float)map_size);
				terrdata->AddVertex(aeVector3(x, y, z));

				x = X + step_size;
				y = Height(X + step_size, Y);
				z = Y;

				terrdata->SetTexCoord((float)x / (float)map_size, (float)z / (float)map_size);
				terrdata->AddVertex(aeVector3(x, y, z));
			}
		} else {   
			for(Y = 0; Y <= map_size; Y += step_size) {
				x = X + step_size;
				y = Height(X + step_size, Y);
				z = Y;

				terrdata->SetTexCoord((float)x / (float)map_size, (float)z / (float)map_size);
				terrdata->AddVertex(aeVector3(x, y, z));

				x = X;           
				y = Height(X, Y);
				z = Y;

				terrdata->SetTexCoord((float)x / (float)map_size, (float)z / (float)map_size);
				terrdata->AddVertex(aeVector3(x, y, z));
			}
		}
		bSwitchSides = !bSwitchSides;
	}
}

int aeTerrMan::Height(int x, int y)
{
	int Hx = x % map_size;
	int Hy = y % map_size;

	return heightmapdata[Hx + (Hy * map_size)];
}

void aeTerrMan::SetOrigin(float x, float y, float z)
{
	terrdata->SetOrigin(aeVector3(x, y, z));
}

void aeTerrMan::SetOrigin(aeVector3 cVec)
{
	terrdata->SetOrigin(cVec);
}

void aeTerrMan::SetMaterial(aeMaterial *mat)
{
	terrdata->SetMaterial(mat);
}

bool aeTerrMan::LoadHeightMap(char *filename)
{
	FILE *pFile = NULL;

	pFile = fopen(filename, "rb");

	if(pFile == NULL) {
		Report(0, "Can't open heighmap file\n");
		return false;
	}

	heightmapdata = new unsigned char[map_size * map_size];
	fread(heightmapdata, 1, map_size * map_size, pFile);

	int result = ferror(pFile);

	// Check if we received an error.
	if(result) {
		Report(0, "Can't read heightmap file\n");
		return false;
	}

	fclose(pFile);

	BuildHeightMapVertices();

	return true;
}

extern "C" aePlugin *PLUGIN_ENTRY(aeRegistry *aeReg)
{
  aeTerrMan *terrmanptr = new aeTerrMan(aeReg);
  return terrmanptr;
}
