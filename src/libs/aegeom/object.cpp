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
#include <aegeom/object.h>
#include <aegeom/vector3.h>
#include <aegfx/color3.h>
#include <aegfx/color4.h>
#include <aegfx/material.h>
#include <aegfx/texcoord2.h>

aeObject::~aeObject()
{
	vertexList->clear();
	delete vertexList;
	vertexColorList->clear();
	delete vertexColorList;
	vertexTexcoordList->clear();
	delete vertexTexcoordList;
}

aeVector3 aeObject::GetOrigin()
{
	return origin;
}

void aeObject::SetOrigin(const aeVector3 &norigin)
{
	origin = norigin;
}

void aeObject::SetColor(float r, float g, float b)
{
	currentVertexColor.red = r;
	currentVertexColor.green = g;
	currentVertexColor.blue = b;
}

void aeObject::SetColor(float r, float g, float b, float a)
{
	currentVertexColor.red = r;
	currentVertexColor.green = g;
	currentVertexColor.blue = b;
	currentVertexColor.alpha = a;
}

void aeObject::SetColor(const aeColor3 &color)
{
	currentVertexColor.red = color.red;
	currentVertexColor.green = color.green;
	currentVertexColor.blue = color.blue;
}

void aeObject::SetColor(const aeColor4 &color)
{
	currentVertexColor = color;
}

void aeObject::SetTexCoord(float s, float t)
{
	currentVertexTexcoord.s = s;
	currentVertexTexcoord.t = t;
}

void aeObject::SetTexCoord(const aeTexCoord2 &texcoord)
{
	currentVertexTexcoord = texcoord;
}

void aeObject::SetMaterial(aeMaterial *mat)
{
	material = mat;

	if(material->GetTextureCount() > 0) {
		hasMaterial = true;

		if(material->HasPrimary()) {
			glBindTexture(GL_TEXTURE_2D, material->GetPrimaryTexture()->t_id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, material->GetPrimaryTexture()->GetWidth(),
							  material->GetPrimaryTexture()->GetHeight(), GL_RGB, GL_UNSIGNED_BYTE,
							  material->GetPrimaryTexture()->GetData());
		}
		if(material->HasSecondary()) {
			glBindTexture(GL_TEXTURE_2D, material->GetSecondaryTexture()->t_id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, material->GetSecondaryTexture()->GetWidth(),
							  material->GetSecondaryTexture()->GetHeight(), GL_RGB, GL_UNSIGNED_BYTE,
							  material->GetSecondaryTexture()->GetData());
		}
	}
}

void aeObject::AddVertex(const aeVector3 &vertex)
{
	vertexColorList->push_back(currentVertexColor);
	vertexTexcoordList->push_back(currentVertexTexcoord);
	vertexList->push_back(vertex);
}

void aeObject::SetTransparent(bool tp)
{
	isTransparent = tp;
}

char *aeObject::GetName()
{
	return objName;
}

unsigned int aeObject::GetVertexCount()
{
	return vertexList->size();
}

aeVector3 aeObject::GetVertex(int v)
{
	return vertexList->at(v);
}

float aeObject::GetBoundingSphereRadius()
{
	aeVector3 vertex;
	float currDist = 0.0;
	unsigned int i;

	if(objRadius == 0.0) {
		for(i = 0; i < vertexList->size(); i++) {
			vertex = vertexList->at(i) - origin;
			currDist = vertex.Magnitude();
			if(currDist > objRadius)
				objRadius = currDist;
		}
	}

	return objRadius;
}

aeMaterial *aeObject::GetMaterial()
{
	return material;
}

bool aeObject::IsTransparent()
{
	return (isTransparent ? true : false);
}

void aeObject::SetMode(aeObjRenderingMode mode)
{
	objRenderMode = mode;
}
