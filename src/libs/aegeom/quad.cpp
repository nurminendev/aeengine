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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <aedefs.h>
#include <aeengine/eflags.h>
#ifdef WIN32
#include <aeengine/win32/glproc.h>
#endif
#include <aegeom/quad.h>
#include <aegeom/vector3.h>
#include <aegfx/color3.h>
#include <aegfx/color4.h>
#include <aegfx/material.h>
#include <aegfx/texcoord2.h>
#include <aegfx/texture.h>
#include <aeutil/util.h>

aeQuad::aeQuad()
{
	AECF_CNAME("aeQuad")
	vertexList = new std::vector<aeVector3>();
	vertexList->resize(0);
	if(DEBUG) {
		ASSERT(vertexList->size() == 0, "vertexList->size() == 0");
	}

	vertexColorList = new std::vector<aeColor4>();
	vertexColorList->resize(0);
	if(DEBUG) {
		ASSERT(vertexColorList->size() == 0, "vertexColorList->size() == 0");
	}

	vertexTexcoordList = new std::vector<aeTexCoord2>();
	vertexTexcoordList->resize(0);
	if(DEBUG) {
		ASSERT(vertexTexcoordList->size() == 0, "vertexTexcoordList->size() == 0");
	}

	origin = aeVector3(0.0, 0.0, 0.0);
	currentVertexColor = aeColor4(1.0, 1.0, 1.0, 1.0);
	currentVertexTexcoord = aeTexCoord2(0.0, 0.0);
	hasMaterial = false;
	objRenderMode = QUADS_NORMAL;
	objName = "";
	isTransparent = false;
	objRadius = 0.0;
}

aeQuad::aeQuad(char *objname)
{
	vertexList = new std::vector<aeVector3>();
	vertexList->resize(0);
	if(DEBUG) {
		ASSERT(vertexList->size() == 0, "vertexList->size() == 0");
	}

	vertexColorList = new std::vector<aeColor4>();
	vertexColorList->resize(0);
	if(DEBUG) {
		ASSERT(vertexColorList->size() == 0, "vertexColorList->size() == 0");
	}

	vertexTexcoordList = new std::vector<aeTexCoord2>();
	vertexTexcoordList->resize(0);
	if(DEBUG) {
		ASSERT(vertexTexcoordList->size() == 0, "vertexTexcoordList->size() == 0");
	}

	origin = aeVector3(0.0, 0.0, 0.0);
	currentVertexColor = aeColor4(1.0, 1.0, 1.0, 1.0);
	currentVertexTexcoord = aeTexCoord2(0.0, 0.0);
	hasMaterial = false;
	objRenderMode = QUADS_NORMAL;
	objName = objname;
	isTransparent = false;
	objRadius = 0.0;
}

aeQuad::~aeQuad()
{
}

void aeQuad::Draw(aeEngineflags *eflags)
{
	aeVector3 tempvec;
	aeColor4 tempcolor;
	aeTexCoord2 temptexcoord;

	if(hasMaterial) {
		if(eflags->hasMultitexture) {
			if(material->HasPrimary()) {
#ifdef WIN32
				glProc::glActiveTextureARB(GL_TEXTURE0_ARB);
#else
				glActiveTextureARB(GL_TEXTURE0_ARB);
#endif
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, material->GetPrimaryTexture()->t_id);
				if(material->GetPrimaryTexture()->GetTexMode() == BLEND) {
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
				} else if(material->GetPrimaryTexture()->GetTexMode() == DECAL) {
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				} else if(material->GetPrimaryTexture()->GetTexMode() == MODULATE) {
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				} else if(material->GetPrimaryTexture()->GetTexMode() == REPLACE) {
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
				}
			}
			if(material->HasSecondary()) {
#ifdef WIN32
				glProc::glActiveTextureARB(GL_TEXTURE1_ARB);
#else
				glActiveTextureARB(GL_TEXTURE1_ARB);
#endif
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, material->GetSecondaryTexture()->t_id);
				if(material->GetSecondaryTexture()->GetTexMode() == BLEND) {
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
				} else if(material->GetSecondaryTexture()->GetTexMode() == DECAL) {
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				} else if(material->GetSecondaryTexture()->GetTexMode() == MODULATE) {
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				} else if(material->GetSecondaryTexture()->GetTexMode() == REPLACE) {
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
				}
			}
		} else {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, material->GetPrimaryTexture()->t_id);
			if(material->GetPrimaryTexture()->GetTexMode() == BLEND) {
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
			} else if(material->GetPrimaryTexture()->GetTexMode() == DECAL) {
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			} else if(material->GetPrimaryTexture()->GetTexMode() == MODULATE) {
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			} else if(material->GetPrimaryTexture()->GetTexMode() == REPLACE) {
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			}
		}
	}

	if(isTransparent) {
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	glPushMatrix();
	  glTranslatef(origin.x, origin.y, origin.z);

	  if(objRenderMode == QUADS_NORMAL)
		  glBegin(GL_QUADS);
	  else if(objRenderMode == QUADS_STRIP)
		  glBegin(GL_QUAD_STRIP);
	  else
		  glBegin(GL_QUADS);

	  for(unsigned int i = 0; i < vertexList->size(); i++) {
		  tempvec = vertexList->at(i);
		  if(hasMaterial) {
			  temptexcoord = vertexTexcoordList->at(i);
			  if(eflags->hasMultitexture) {
				  if(material->HasPrimary()) {
#ifdef WIN32
					  glProc::glMultiTexCoord2fARB(GL_TEXTURE0_ARB, temptexcoord.s, temptexcoord.t);
#else
					  glMultiTexCoord2fARB(GL_TEXTURE0_ARB, temptexcoord.s, temptexcoord.t);
#endif
				  }
				  if(material->HasSecondary()) {
#ifdef WIN32
					  glProc::glMultiTexCoord2fARB(GL_TEXTURE1_ARB, temptexcoord.s, temptexcoord.t);
#else
					  glMultiTexCoord2fARB(GL_TEXTURE1_ARB, temptexcoord.s, temptexcoord.t);
#endif
				  }
			  } else {
				  glTexCoord2f(temptexcoord.s, temptexcoord.t);
			  }
		  } else {
			  tempcolor = vertexColorList->at(i);
			  glColor4f(tempcolor.red, tempcolor.green, tempcolor.blue, tempcolor.alpha);
		  }
		  glVertex3f(tempvec.x, tempvec.y, tempvec.z);
	  }
	  glEnd();
	glPopMatrix();

	if(isTransparent) {
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	if(hasMaterial) {
		if(eflags->hasMultitexture) {
			if(material->HasSecondary()) {
#ifdef WIN32
				glProc::glActiveTextureARB(GL_TEXTURE1_ARB);
#else
				glActiveTextureARB(GL_TEXTURE1_ARB);
#endif
				glDisable(GL_TEXTURE_2D);
			}
			if(material->HasPrimary()) {
#ifdef WIN32
				glProc::glActiveTextureARB(GL_TEXTURE0_ARB);
#else
				glActiveTextureARB(GL_TEXTURE0_ARB);
#endif
				glDisable(GL_TEXTURE_2D);
			}
		} else {
			glDisable(GL_TEXTURE_2D);
		}
	}
}
