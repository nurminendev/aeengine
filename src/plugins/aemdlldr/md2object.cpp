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
#include <aeengine/eflags.h>
#ifdef WIN32
#include <aeengine/win32/glproc.h>
#endif
#include <aegeom/model.h>
#include <aegeom/vector3.h>
#include <aegfx/material.h>
#include <aegfx/texcoord2.h>
#include <aegfx/texture.h>
#include <aemdlldr/md2object.h>
#include <aemdlldr/mdlstruct.h>
#include <aeutil/util.h>

aeMD2Object::aeMD2Object(char *mdlstr, aeVector3_vector *vertList, aeTexCoord2_vector *stList,
						 mesh_t *triIdx, unsigned int numframes, unsigned int numverts,
						 unsigned int numtris, unsigned int numst, unsigned int framesize)
{
	AECF_CNAME("aeMD2Object")
	vertexList = vertList;
	vertexTexcoordList = stList;
	vertexColorList = new aeColor4_vector();
	triIndex = triIdx;
	origin = aeVector3(0.0, 0.0, 0.0);
	currentVertexColor = aeColor4(1.0, 1.0, 1.0, 1.0);
	currentVertexTexcoord = aeTexCoord2(0.0, 0.0);
	hasMaterial = false;
	objRenderMode = TRIANGLES_NORMAL;
	objName = mdlstr;
	modelState = MODEL_IDLE;
	isAnimating = false;
	material = NULL;
	isTransparent = false;
	objRadius = 0.0;

	// Number of frames, vertices, triangles and texcoords.
	numFrames = numframes;
	numVertices = numverts;
	numTriangles = numtris;
	numTexCoords = numst;

	// Init frame infos.
	frameSize = framesize;
	currentFrame = 0;
	nextFrame = 1;
	interpol = 0.0;
	startFrame = 0;
	endFrame = 0;
	interpol = 0.0;
	keyFrame = 0;
}

aeMD2Object::~aeMD2Object()
{
	if(triIndex)
		delete triIndex;
}

void aeMD2Object::Draw(aeEngineflags *eflags)
{
	if(isAnimating)
		Animate(eflags);
	else
		RenderFrame(eflags);
}

int aeMD2Object::Animate(aeEngineflags *eflags)
{
	aeVector3 ivertex[3], inormal;
	aeVector3 p1, p2;
	unsigned int curFrameVListIdx, nextFrameVListIdx;
	unsigned int i;
     
	if((startFrame > currentFrame))
		currentFrame = startFrame;

	if((startFrame < 0) || (endFrame < 0))
		return -1;

	if((startFrame >= (int)numFrames) || (endFrame >= (int)numFrames))
		return -1;

	if(interpol >= 1.0) {
		interpol = 0.0f;
		currentFrame++;
		if(currentFrame >= endFrame)
			currentFrame = startFrame;

		nextFrame = currentFrame + 1;

		if(nextFrame >= endFrame)
			nextFrame = startFrame;
	}

	curFrameVListIdx = numVertices * currentFrame;
	nextFrameVListIdx = numVertices * nextFrame;

	if(hasMaterial) {
		if(eflags->hasMultitexture) {
			if(material->HasPrimary()) {
#ifndef WIN32
				glActiveTextureARB(GL_TEXTURE0_ARB);
#else
				glProc::glActiveTextureARB(GL_TEXTURE0_ARB);
#endif
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, material->GetPrimaryTexture()->t_id);
			}
			if(material->HasSecondary()) {
#ifndef WIN32
				glActiveTextureARB(GL_TEXTURE1_ARB);
#else
				glProc::glActiveTextureARB(GL_TEXTURE1_ARB);
#endif
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, material->GetSecondaryTexture()->t_id);
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
			}
		}
	}

	glPushMatrix();
	glTranslatef(origin.x, origin.y, origin.z);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	glRotatef(155.0, 0.0, 0.0, 1.0);

	glBegin(GL_TRIANGLES);
	for(i = 0; i < numTriangles; i++) {
		// Get first vertex of this and the next triangle.
		p1 = vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[0]);
		p2 = vertexList->at(nextFrameVListIdx + triIndex[i].meshIndex[0]);

		// Store first interpolated vertex of the triangle.
		ivertex[0] = p1 + interpol * (p2 - p1);

		// Get second vertex of this and the next triangle.
		p1 = vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[2]);
		p2 = vertexList->at(nextFrameVListIdx + triIndex[i].meshIndex[2]);

		// Store second interpolated vertex of the triangle.
		ivertex[2] = p1 + interpol * (p2 - p1);

		// Get third vertex of this and the next triangle.
		p1 = vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[1]);
		p2 = vertexList->at(nextFrameVListIdx + triIndex[i].meshIndex[1]);

		// Store third interpolated vertex.
		ivertex[1] = p1 + interpol * (p2 - p1);

		// Calculate normal for the interpolated triangle.
		inormal = aeUtil::CalculateNormal(ivertex[0], ivertex[2], ivertex[1]);
		glNormal3f(inormal.x, inormal.y, inormal.z);

		if(hasMaterial) {
			if(eflags->hasMultitexture) {
				if(material->HasPrimary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[0]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[0]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[0]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[0]).t);
#endif
				}
				if(material->HasSecondary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[0]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[0]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[0]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[0]).t);
#endif
				}
			} else {
				glTexCoord2f(vertexTexcoordList->at(triIndex[i].stIndex[0]).s,
							 vertexTexcoordList->at(triIndex[i].stIndex[0]).t);
			}
		}
		glVertex3f(ivertex[0].x, ivertex[0].y, ivertex[0].z);

		if(hasMaterial) {
			if(eflags->hasMultitexture) {
				if(material->HasPrimary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[2]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[2]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[2]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[2]).t);
#endif
				}
				if(material->HasSecondary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[2]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[2]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[2]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[2]).t);
#endif
				}
			} else {
				glTexCoord2f(vertexTexcoordList->at(triIndex[i].stIndex[2]).s,
							 vertexTexcoordList->at(triIndex[i].stIndex[2]).t);
			}
		}
		glVertex3f(ivertex[2].x, ivertex[2].y, ivertex[2].z);

		if(hasMaterial) {
			if(eflags->hasMultitexture) {
				if(material->HasPrimary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[1]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[1]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[1]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[1]).t);
#endif
				}
				if(material->HasSecondary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[1]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[1]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[1]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[1]).t);
#endif
				}
			} else {
				glTexCoord2f(vertexTexcoordList->at(triIndex[i].stIndex[1]).s,
							 vertexTexcoordList->at(triIndex[i].stIndex[1]).t);
			}
		}
		glVertex3f(ivertex[1].x, ivertex[1].y, ivertex[1].z);
	}
	glEnd();

	glPopMatrix();

	if(hasMaterial) {
		if(eflags->hasMultitexture) {
			if(material->HasSecondary()) {
#ifndef WIN32
				glActiveTextureARB(GL_TEXTURE1_ARB);
#else
				glProc::glActiveTextureARB(GL_TEXTURE1_ARB);
#endif
				glDisable(GL_TEXTURE_2D);
			}
			if(material->HasPrimary()) {
#ifndef WIN32
				glActiveTextureARB(GL_TEXTURE0_ARB);
#else
				glProc::glActiveTextureARB(GL_TEXTURE0_ARB);
#endif
				glDisable(GL_TEXTURE_2D);
			}
		} else {
			glDisable(GL_TEXTURE_2D);
		}
	}

	interpol += percent;

	return 0;
}

int aeMD2Object::RenderFrame(aeEngineflags *eflags)
{
	aeVector3 normal;
	unsigned int curFrameVListIdx;
	unsigned int i;

	curFrameVListIdx = numVertices * keyFrame;

	if(hasMaterial) {
		if(eflags->hasMultitexture) {
			if(material->HasPrimary()) {
#ifndef WIN32
				glActiveTextureARB(GL_TEXTURE0_ARB);
#else
				glProc::glActiveTextureARB(GL_TEXTURE0_ARB);
#endif
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, material->GetPrimaryTexture()->t_id);
			}
			if(material->HasSecondary()) {
#ifndef WIN32
				glActiveTextureARB(GL_TEXTURE1_ARB);
#else
				glProc::glActiveTextureARB(GL_TEXTURE1_ARB);
#endif
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, material->GetSecondaryTexture()->t_id);
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
			}
		}
	}

	glPushMatrix();
	glTranslatef(origin.x, origin.y, origin.z);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glRotatef(135.0, 0.0, 0.0, 1.0);

	// Display the textured model with proper lighting normals.
	glBegin(GL_TRIANGLES);
	for(i = 0; i < numTriangles; i++) {
		normal = aeUtil::CalculateNormal(vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[0]),
										 vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[2]),
										 vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[1]));
		glNormal3f(normal.x, normal.y, normal.z);

		if(hasMaterial) {
			if(eflags->hasMultitexture) {
				if(material->HasPrimary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[0]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[0]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[0]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[0]).t);
#endif
				}
				if(material->HasSecondary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[0]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[0]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[0]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[0]).t);
#endif
				}
			} else {
				glTexCoord2f(vertexTexcoordList->at(triIndex[i].stIndex[0]).s,
							 vertexTexcoordList->at(triIndex[i].stIndex[0]).t);
			}
		}
		glVertex3f(vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[0]).x,
				   vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[0]).y,
				   vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[0]).z);

		if(hasMaterial) {
			if(eflags->hasMultitexture) {
				if(material->HasPrimary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[2]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[2]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[2]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[2]).t);
#endif
				}
				if(material->HasSecondary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[2]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[2]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[2]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[2]).t);
#endif
				}
			} else {
				glTexCoord2f(vertexTexcoordList->at(triIndex[i].stIndex[2]).s,
							 vertexTexcoordList->at(triIndex[i].stIndex[2]).t);
			}
		}
		glVertex3f(vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[2]).x,
				   vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[2]).y,
				   vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[2]).z);

		if(hasMaterial) {
			if(eflags->hasMultitexture) {
				if(material->HasPrimary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[1]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[1]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE0_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[1]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[1]).t);
#endif
				}
				if(material->HasSecondary()) {
#ifndef WIN32
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
										 vertexTexcoordList->at(triIndex[i].stIndex[1]).s,
										 vertexTexcoordList->at(triIndex[i].stIndex[1]).t);
#else
					glProc::glMultiTexCoord2fARB(GL_TEXTURE1_ARB,
												 vertexTexcoordList->at(triIndex[i].stIndex[1]).s,
												 vertexTexcoordList->at(triIndex[i].stIndex[1]).t);
#endif
				}
			} else {
				glTexCoord2f(vertexTexcoordList->at(triIndex[i].stIndex[1]).s,
							 vertexTexcoordList->at(triIndex[i].stIndex[1]).t);
			}
		}
		glVertex3f(vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[1]).x,
				   vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[1]).y,
				   vertexList->at(curFrameVListIdx + triIndex[i].meshIndex[1]).z);
	}
	glEnd();

	glPopMatrix();

	if(hasMaterial) {
		if(eflags->hasMultitexture) {
			if(material->HasSecondary()) {
#ifndef WIN32
				glActiveTextureARB(GL_TEXTURE1_ARB);
#else
				glProc::glActiveTextureARB(GL_TEXTURE1_ARB);
#endif
				glDisable(GL_TEXTURE_2D);
			}
			if(material->HasPrimary()) {
#ifndef WIN32
				glActiveTextureARB(GL_TEXTURE0_ARB);
#else
				glProc::glActiveTextureARB(GL_TEXTURE0_ARB);
#endif
				glDisable(GL_TEXTURE_2D);
			}
		} else {
			glDisable(GL_TEXTURE_2D);
		}
	}

	return 0;
}

void aeMD2Object::SetState(modelState_t state)
{
	modelState = state;
}

modelState_t aeMD2Object::GetState()
{
	return modelState;
}

void aeMD2Object::SetAnimation(int startframe, int endframe, float percent)
{
	startFrame = startframe;
	endFrame = endframe;
	this->percent = percent;
	isAnimating = true;
}

void aeMD2Object::SetFrame(int keyframe)
{
	keyFrame = keyframe;
	isAnimating = false;
}
