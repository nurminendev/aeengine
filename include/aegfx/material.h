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

#ifndef __AELIB_AEGFX_MATERIAL_H__
#define __AELIB_AEGFX_MATERIAL_H__

#include <aedefs.h>
#include <aegfx/texture.h>
#include <aereg/base.h>

/** 
 * This class represents a material that can be applied onto an object.
 * 
 */
class aeMaterial: public aeBase {
	AECF_CNDEF

 private:
	aeTexture *tex1;
	aeTexture *tex2;
	int texcount;
	char *matname;

 public:
	/** 
	 * Create a empty material.
	 * 
	 */
	aeMaterial();

	/** 
	 * Create a material given a name and a primary texture.
	 * 
	 * @param char * The material's name.
	 * @param  aeTexture * The material's primary texture.
	 */
	aeMaterial(char *, aeTexture *);

	/** 
	 * Createa a material given a name and a primary texture and a secondary texture.
	 * 
	 * @param char * The material's name.
	 * @param  aeTexture * The material's primary texture.
	 * @param  aeTexture * The material's secondary texture.
	 */
	aeMaterial(char *, aeTexture *, aeTexture *);
	~aeMaterial();

	/** 
	 * Get the material's name.
	 * 
	 * 
	 * @return The material's name.
	 */
	char *GetName() const { return matname; }

	/** 
	 * Get The primary texture of this material.
	 * 
	 * 
	 * @return The primary texture.
	 */
	aeTexture *GetPrimaryTexture() const { return tex1; }

	/** 
	 * Get the secondary texture of this material.
	 * 
	 * 
	 * @return The secondary texture.
	 */
	aeTexture *GetSecondaryTexture() const { return tex2; }

	/** 
	 * Add a texture to this material.
	 * If the material is empty, the texture will be added as primary. If only primary texture is
	 * present, the texture will be added as secondary. If both primary and secondary textures are
	 * present this will simply do nothing.
	 * 
	 * @param aeTexture * The texture to add.
	 */
	void AddTexture(aeTexture *);

	/** 
	 * Set the primary texture of this material.
	 * 
	 * @param aeTexture * The primary texture.
	 */
	void SetPrimaryTexture(aeTexture *);

	/** 
	 * Set the secondary texture of this material.
	 * 
	 * @param aeTexture * The secondary texture.
	 */
	void SetSecondaryTexture(aeTexture *);

	/** 
	 * Get the texture count for this material.
	 * Can be either 0, 1, or 2.
	 * 
	 * 
	 * @return The texture count.
	 */
	unsigned int GetTextureCount() const { return texcount; }

	/** 
	 * Check if this material has a primary texture.
	 * 
	 * 
	 * @return True if the material has a primary texture.
	 */
	bool HasPrimary();

	/** 
	 * Check if this material has a secondary texture.
	 * 
	 * 
	 * @return True if the material has a secondary texture.
	 */
	bool HasSecondary();
};

#endif // __AELIB_AEGFX_MATERIAL_H__
