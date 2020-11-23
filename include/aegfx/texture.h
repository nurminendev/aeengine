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

#ifndef __AELIB_AEGFX_TEXTURE_H__
#define __AELIB_AEGFX_TEXTURE_H__

#include <aedefs.h>
#include <aereg/base.h>

enum aeTexMode {
	REPLACE,
	BLEND,
	DECAL,
	MODULATE
};

/** 
 * A single texture object.
 */
class aeTexture: public aeBase {
	AECF_CNDEF

 private:
	unsigned char *t_buffer;
	unsigned int t_width;
	unsigned int t_height;
	unsigned int t_bpp;
	char *t_string;
	aeTexMode t_texmode;

 public:
	/** 
	 * Create a texture.
	 * Normally you don't never do this yourself, since the texture loader will do it.
	 * 
	 */
	aeTexture(char *, unsigned char *, unsigned int width, unsigned int height, unsigned int bpp);
	~aeTexture();

	/// This is the texture's id.
	GLuint t_id;

	/** 
	 * Get the texture's data.
	 * 
	 * 
	 * @return The texture's data.
	 */
	unsigned char *GetData() const { return t_buffer; }

	/** 
	 * Get the texture's name.
	 * 
	 * 
	 * @return The texture's name.
	 */
	char *GetName() const { return t_string; }

	/** 
	 * Get the texture's width.
	 * 
	 * 
	 * @return The texture's width
	 */
	unsigned int GetWidth() const { return t_width; }

	/** 
	 * Get the texture's height
	 * 
	 * 
	 * @return the texture's height
	 */
	unsigned int GetHeight() const { return t_height; }

	/** 
	 * Get the BPP for the texture.
	 * 
	 * 
	 * @return The BPP value for the texture.
	 */
	int GetBitsPerPixel() const { return t_bpp; }

	/** 
	 * Get the texture mode for this texture.
	 * 
	 * 
	 * @return The texture mode
	 */
	aeTexMode GetTexMode() const { return t_texmode; }

	/** 
	 * Set the texture mode for this texture.
	 * Available texture modes are:
	 * <ul>
	 *   <li>REPLACE
	 *   <li>BLEND
	 *   <li>DECAL
	 *   <li>MODULATE
	 * </ul>
	 *
	 * 
	 * @param aeTexMode The texturemode
	 */
	void SetTexMode(aeTexMode);
};

#endif // __AELIB_AEGFX_TEXTURE_H__
