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
#include <aegfx/texture.h>

aeTexture::aeTexture(char *tstring, unsigned char *imgdata, unsigned int width, unsigned int height, unsigned int bpp)
{
	AECF_CNAME("aeTexture")
	t_buffer = imgdata;
	t_width = width;
	t_height = height;
	t_bpp = bpp;
	t_string = tstring;
	t_texmode = DECAL;
	glGenTextures(1, &t_id);
}

aeTexture::~aeTexture()
{
	if(t_buffer != NULL) {
		delete t_buffer;
	}
}

void aeTexture::SetTexMode(aeTexMode texmode)
{
	t_texmode = texmode;
}
