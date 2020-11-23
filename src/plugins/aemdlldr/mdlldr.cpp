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
#include <aegeom/model.h>
#include <aegfx/material.h>
#include <aegfx/texcoord2.h>
#include <aemdlldr/md2object.h>
#include <aemdlldr/mdlldr.h>
#include <aemdlldr/mdlstruct.h>
#include <aeplugin/plugin.h>
#include <aereg/registry.h>

aeModelLoader::aeModelLoader(aeRegistry *aeReg)
{
	AECF_CNAME("aeModelLoader")
	myID = AE_PLUGIN_aeModelLoader;

	aereg = aeReg;
}

aeModelLoader::~aeModelLoader()
{
}

aeModelType aeModelLoader::GetModelType(char *mdlfile)
{
	char *ptr;
	if((ptr = strrchr(mdlfile, '.')) != NULL) {
		if(strstr(ptr + 1, "md2"))
			return AE_MODEL_MD2;
	}
	return AE_MODEL_UNKNOWN;
}

aeModel *aeModelLoader::LoadModel(char *mdlname, char *mdlfile, aeMaterial *mat)
{
	aeModel *mdl = NULL;

	switch(GetModelType(mdlfile)) {
	case AE_MODEL_MD2:
		if(mat == NULL)
			mdl = LoadMD2(mdlname, mdlfile);
		else
			mdl = LoadMD2(mdlname, mdlfile, mat);
		break;
	case AE_MODEL_UNKNOWN:
		break;
	default:
		break;
	}

	if(mdl != NULL)
		aereg->PushObjectToPool(mdl);

	return mdl;
}

aeMD2Object *aeModelLoader::LoadMD2(char *mdlstr, char *modelFile)
{
	FILE *filePtr;
	aeMD2Object *md2obj;
	int fileLen;
	char *buffer;
	unsigned int i, j;
	md2Header_t *md2Header;
	frame_t *frame;
	stIndex_t *stPtr;
	mesh_t *bufIndexPtr;
	mesh_t *triIndex;
	aeTexCoord2_vector *texcoordList = new aeTexCoord2_vector();
	aeVector3_vector *vertexList = new aeVector3_vector();

	// Reset the vectors
	texcoordList->resize(0);
	vertexList->resize(0);

	// Open model file
	filePtr = fopen(modelFile, "rb");
	if(filePtr == NULL) {
		return NULL;
	}

	fseek(filePtr, 0, SEEK_END);
	fileLen = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);

	// Read entire file into buffer.
	buffer = new char[fileLen + 1];
	fread(buffer, sizeof(char), fileLen, filePtr);

	md2Header = (md2Header_t *)buffer;

	for(j = 0; j < md2Header->numFrames; j++) {
		frame = (frame_t *)&buffer[md2Header->offsetFrames + md2Header->frameSize * j];
		for(i = 0; i < md2Header->numVertices; i++) {
			vertexList->push_back(aeVector3(frame->scale[0] * frame->fp[i].v[0] + frame->translate[0],
											frame->scale[1] * frame->fp[i].v[1] + frame->translate[1],
											frame->scale[2] * frame->fp[i].v[2] + frame->translate[2])
								  );
		}
	}

	stPtr = (stIndex_t *)&buffer[md2Header->offsetST];
	for(i = 0; i < md2Header->numTexCoords; i++) {
		texcoordList->push_back(aeTexCoord2((float)stPtr[i].s,
											(float)stPtr[i].t));
	}

	triIndex = new mesh_t[md2Header->numTriangles];

	// Point to triangle indexes in buffer
	bufIndexPtr = (mesh_t *)&buffer[md2Header->offsetTris];

	// Create a mesh (triangle) list
	for(j = 0; j < md2Header->numFrames; j++) {
		for(i = 0; i < md2Header->numTriangles; i++) {
			triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
			triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
			triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
			triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
			triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
			triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
		}
	}
     
	fclose(filePtr);

	md2obj = new aeMD2Object(mdlstr, vertexList, texcoordList, triIndex, md2Header->numFrames,
							 md2Header->numVertices, md2Header->numTriangles, md2Header->numTexCoords,
							 md2Header->frameSize);

	md2Header = NULL;
	frame = NULL;
	bufIndexPtr = NULL;
	delete buffer;

	return md2obj;
}

aeMD2Object *aeModelLoader::LoadMD2(char *mdlstr, char *modelFile, aeMaterial *mat)
{
	FILE *filePtr;
	aeMD2Object *md2obj;
	int fileLen;
	char *buffer;
	unsigned int i, j;
	md2Header_t *md2Header;
	frame_t *frame;
	stIndex_t *stPtr;
	mesh_t *bufIndexPtr;
	mesh_t *triIndex;
	aeTexCoord2_vector *texcoordList = new aeTexCoord2_vector();
	aeVector3_vector *vertexList = new aeVector3_vector();

	// Reset the vectors
	texcoordList->resize(0);
	vertexList->resize(0);

	// Open model file
	filePtr = fopen(modelFile, "rb");
	if(filePtr == NULL) {
		return NULL;
	}

	fseek(filePtr, 0, SEEK_END);
	fileLen = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);

	// Read entire file into buffer.
	buffer = new char[fileLen + 1];
	fread(buffer, sizeof(char), fileLen, filePtr);
     
	md2Header = (md2Header_t *)buffer;

	for(j = 0; j < md2Header->numFrames; j++) {
		frame = (frame_t *)&buffer[md2Header->offsetFrames + md2Header->frameSize * j];
		for(i = 0; i < md2Header->numVertices; i++) {
			vertexList->push_back(aeVector3(frame->scale[0] * frame->fp[i].v[0] + frame->translate[0],
											frame->scale[1] * frame->fp[i].v[1] + frame->translate[1],
											frame->scale[2] * frame->fp[i].v[2] + frame->translate[2])
								  );
		}
	}

	stPtr = (stIndex_t *)&buffer[md2Header->offsetST];
	for(i = 0; i < md2Header->numTexCoords; i++) {
		texcoordList->push_back(aeTexCoord2((float)stPtr[i].s / (float)mat->GetPrimaryTexture()->GetWidth(),
											(float)stPtr[i].t / (float)mat->GetPrimaryTexture()->GetHeight()));
	}

	triIndex = new mesh_t[md2Header->numTriangles];
     
	// Point to triangle indexes in buffer
	bufIndexPtr = (mesh_t *)&buffer[md2Header->offsetTris];
     
	// Create a mesh (triangle) list
	for(j = 0; j < md2Header->numFrames; j++) {
		for(i = 0; i < md2Header->numTriangles; i++) {
			triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
			triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
			triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
			triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
			triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
			triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
		}
	}
     
	// close file and free memory
	fclose(filePtr);

	md2obj = new aeMD2Object(mdlstr, vertexList, texcoordList, triIndex, md2Header->numFrames,
							 md2Header->numVertices, md2Header->numTriangles, md2Header->numTexCoords,
							 md2Header->frameSize);
	md2obj->SetMaterial(mat);

	md2Header = NULL;
	frame = NULL;
	stPtr = NULL;
	bufIndexPtr = NULL;
	delete buffer;

	return md2obj;
}

extern "C" aePlugin *PLUGIN_ENTRY(aeRegistry *aeReg)
{
	aeModelLoader *mdlldrptr = new aeModelLoader(aeReg);
	return mdlldrptr;
}
