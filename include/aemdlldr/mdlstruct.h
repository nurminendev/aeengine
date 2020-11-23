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

#ifndef __AEPLUGIN_AEMDLLDR_MDLSTRUCT_H__
#define __AEPLUGIN_AEMDLLDR_MDLSTRUCT_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD

/** @defgroup mdlldrstructs AE model loader structures
 * Various structures used by the model loader.
 * @{
 */

/// A model state structure.
enum modelState_t {
	MODEL_IDLE,
	MODEL_CROUCH,
	MODEL_RUN,
	MODEL_JUMP
};

/// A texture coordinate index structure.
typedef struct {
	short s;
	short t;
} stIndex_t;

/// A single frame point structure.
typedef struct {
	/// The point info.
	unsigned char v[3];
	/// Normal index.
	unsigned char normalIndex;
} framePoint_t;

/// A single frame structure.
typedef struct {
	/// Scale values.
	float scale[3];
	/// Translation values.
	float translate[3];
	/// Name of model.
	char name[16];
	/// Beginning of frame vertex list.
	framePoint_t fp[1];
} frame_t;

/// A mesh structure.
typedef struct {
	/// Vertex indices.
	unsigned short meshIndex[3];
	/// Texture coordinate indices.
	unsigned short stIndex[3];
} mesh_t;

/// A MD2 header structure.
typedef struct {
	/// MD2 file ident. Should be equal to "IDP2" (ID polygon 2)
	int ident;
	/// MD2 file version. Should be equal to 8.
	int version;
	/// Width of texture.
	int skinwidth;
	/// Height of texture.
	int skinheight;
	/// Number of bytes per frame.
	unsigned int frameSize;
	/// Number of textures.
	int numSkins;
	/// Number of vertices.
	unsigned int numVertices;
	/// Number of texture coordinates.
	unsigned int numTexCoords;
	/// Number of triangles.
	unsigned int numTriangles;
	/// Number of OpenGL command bytes.
	int numGLcmds;
	/// Number of frames.
	unsigned int numFrames;
	/// Offset to skin names.
	int offsetSkins;
	/// Offset to texture coordinates.
	int offsetST;
	/// Offset of triangle mesh.
	int offsetTris;
	/// Offset of frame data (vertices).
	int offsetFrames;
	/// Offset of OpenGL commands.
	int offsetGLcmds;
	// EOF
	int offsetEnd;
} md2Header_t;

/** @} */

#endif // __AEPLUGIN_AEMDLLDR_MDLSTRUCT_H__
