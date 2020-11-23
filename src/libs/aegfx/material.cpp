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
#include <aegfx/material.h>
#include <aegfx/texture.h>
#include <aereg/registry.h>
#include <aeutil/util.h>

aeMaterial::aeMaterial()
{
	AECF_CNAME("aeMaterial")
	tex1 = NULL;
	tex2 = NULL;
	texcount = 0;
	matname = "";
	aeRegistry::self_ptr->PushMaterialToPool(this);
}

aeMaterial::aeMaterial(char *matstr, aeTexture *t1)
{
	AECF_CNAME("aeMaterial")
	tex1 = t1;
	tex2 = NULL;
	texcount = 1;
	matname = matstr;
	aeRegistry::self_ptr->PushMaterialToPool(this);
}

aeMaterial::aeMaterial(char *matstr, aeTexture *t1, aeTexture *t2)
{
	AECF_CNAME("aeMaterial")
	tex1 = t1;
	tex2 = t2;
	texcount = 2;
	matname = matstr;
	aeRegistry::self_ptr->PushMaterialToPool(this);
}

aeMaterial::~aeMaterial()
{
}

void aeMaterial::AddTexture(aeTexture *tex)
{
	if(texcount == 0) {
		tex1 = tex;
	} else if(texcount == 1) {
		tex2 = tex;
	}
}

void aeMaterial::SetPrimaryTexture(aeTexture *t1)
{
	tex1 = t1;
}

void aeMaterial::SetSecondaryTexture(aeTexture *t2)
{
	tex2 = t2;
}

bool aeMaterial::HasPrimary()
{
	if(tex1 != NULL)
		return true;

	return false;
}

bool aeMaterial::HasSecondary()
{
	if(tex2 != NULL)
		return true;

	return false;
}
