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

#ifndef __AELIB_AEGEOM_OBJECT_H__
#define __AELIB_AEGEOM_OBJECT_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aeengine/eflags.h>
#include <aegeom/vector3.h>
#include <aegfx/color3.h>
#include <aegfx/color4.h>
#include <aegfx/material.h>
#include <aegfx/texcoord2.h>
#include <aereg/base.h>

/** @addtogroup aeObjRenderingModes AE Object rendering modes
 * Rendering modes for different object types.
 * @{
 */

/** 
 * Object rendering modes. Used to specify a mode in which an object's vertices are interpreted.
 * 
 */
enum aeObjRenderingMode {
 	/// Draw a triangle with 'GL_TRIANGLES' mode.
	/*!
	 * Treats each triplet of vertices as an independent triangle. Vertices 3n - 2, 3n - 1, and 3n
	 * define triangle n.
	 * <br><br>
	 *
	 */
	TRIANGLES_NORMAL,
 	/// Draw a triangle with 'GL_TRIANGLE_STRIP' mode.
	/*!
	 * Draws a connected group of triangles. One triangle is defined for each vertex presented
	 * after the first two vertices. For odd n, vertices n, n + 1, and n + 2 define triangle n.
	 * For even n, vertices n + 1, n, and n + 2 define triangle n. N - 2 triangles are drawn.
	 * <br><br>
	 *
	 */
	TRIANGLES_STRIP,
 	/// Draw a triangle with 'GL_TRIANGLE_FAN' mode.
	/*!
	 * Draws a connected group of triangles. One triangle is defined for each vertex
	 * presented after the first two vertices. Vertices 1, n + 1, and n + 2 define triangle n.
	 * N - 2 triangles are drawn.
	 * <br><br>
	 *
	 */
	TRIANGLES_FAN,

 	/// Draw a quad with 'GL_QUADS' mode.
	/*!
	 * Treats each group of four vertices as an independent quadrilateral. Vertices 4n - 3, 4n - 2,
	 * 4n - 1, and 4n define quadrilateral n. N / 4 quadrilaterals are drawn.
	 * <br><br>
	 *
	 */
	QUADS_NORMAL,
 	/// Draw a quad with 'GL_QUAD_STRIP' mode.
	/*!
	 * Draws a connected group of quadrilaterals. One quadrilateral is defined for each
	 * pair of vertices presented after the first pair. Vertices 2n - 1, 2n, 2n + 2, and 2n + 1
	 * define quadrilateral n. N / 2 - 1 quadrilaterals are drawn. Note that the order in
	 * which vertices are used to construct a quadrilateral from strip data is different from
	 * that used with independent data.
	 * <br><br>
	 *
	 */
	QUADS_STRIP,

	/// Draw a line object with 'GL_LINES' mode.
	/*!
	 * Treats each pair of vertices as an independent line segment. Vertices 2n - 1 and 2n define
	 * line n. N/2 lines are drawn.
	 * <br><br>
	 */
	LINES_NORMAL,
	/// Draw a line object with 'GL_LINE_STRIP' mode.
	/*!
	 * Draws a connected group of line segments from the first vertex to the last. Vertices n and
	 * n + 1 define line n.
	 * <br><br>
	 */
	LINES_STRIP,
	/// Draw a line object with 'GL_LINE_LOOP' mode.
	/*!
	 * Draws a connected group of line segments from the first vertex to the last, then back
	 * to the first. Vertices n and n+1 define line n. The last line, however, is defined by
	 * vertices N and 1. N lines are drawn.
	 * <br><br>
	 */
	LINES_LOOP,

	/// Draw a polygon object with 'GL_POLYGON' mode.
	/*!
	 * Draws a single, convex polygon. Vertices 1 through N define this polygon.
	 */
	POLYGON_NORMAL
};

/** @} */

/** 
 * A base class for all objects
 * 
 */
class aeObject: public aeBase {
 protected:
	std::vector<aeVector3> *vertexList;
	std::vector<aeColor4> *vertexColorList;
	std::vector<aeTexCoord2> *vertexTexcoordList;
	aeVector3 origin;
	aeColor4 currentVertexColor;
	aeTexCoord2 currentVertexTexcoord;
	bool hasMaterial;
	aeMaterial *material;
	char *objName;
	bool isTransparent;
	float objRadius;
	aeObjRenderingMode objRenderMode;

 public:
	virtual ~aeObject();

	/** 
	 * Get object's name.
	 * 
	 * 
	 * @return The object's name.
	 */
	virtual char *GetName();

	/** 
	 * Get the object's material.
	 * 
	 * 
	 * @return The object's material.
	 */
	virtual aeMaterial *GetMaterial();

	/** 
	 * Draw this object. This is called by aeEngine::Render(). You shouldn't need to call
	 * this yourself.
	 * 
	 */
	virtual void Draw(aeEngineflags *) = 0;

	/** 
	 * Get the origin for this object.
	 * 
	 * 
	 * @return The object's origin.
	 */
	virtual aeVector3 GetOrigin();

	/** 
	 * Set the origin for this object.
	 * 
	 * @param o_origin The origin vector.
	 */
	virtual void SetOrigin(const aeVector3 &norigin);

	/** 
	 * Set the RGB color of this object.
	 * The values are from 0.0 to 1.0. Subsequent AddVertex() calls will add a vertex of this color.
	 * 
	 * @param r Red.
	 * @param g Green.
	 * @param b Blue.
	 */
	virtual void SetColor(float r, float g, float b);

	/** 
	 * Set the RGBA color of this object.
	 * The values are from 0.0 to 1.0. Subsequent AddVertex() calls will add a vertex of this color.
	 * 
	 * @param r Red.
	 * @param g Green.
	 * @param b Blue.
	 * @param a Alpha.
	 */
	virtual void SetColor(float r, float g, float b, float a);

	/** 
	 * Set the RGB color of this object.
	 * This accepts an aeColor3 to specify the color. Subsequent AddVertex() calls will add a vertex
	 * of this color.
	 * 
	 * @param color an aeColor3 instance representing the wanted color.
	 */
	virtual void SetColor(const aeColor3 &color);

	/** 
	 * Set the RGBA color of this object.
	 * This accepts an aeColor4 to specify the color. Subsequent AddVertex() calls will add a vertex
	 * of this color.
	 * 
	 * @param color an aeColor4 instance representing the wanted color.
	 */
	virtual void SetColor(const aeColor4 &color);

	/** 
	 * Set the texture coordinate for the next vertex(es).
	 * Use this before AddVertex() to add a texture coordinate for that vertex. If you set a texcoord
	 * only for the first vertex, that coordinate will be used for all subsequent vertices until you
	 * specify a new texture coordinate.
	 * 
	 * @param texcoord a 2D texcoord representing the texture coordinate.
	 */
	virtual void SetTexCoord(const aeTexCoord2 &texcoord);

	/** 
	 * Set the texture coordinate for the next vertex(es).
	 * Use this before AddVertex() to add a texture coordinate for that vertex. If you set a texcoord
	 * only for the first vertex, that coordinate will be used for all subsequent vertices until you
	 * specify a new texture coordinate.
	 * 
	 * @param s The s coordinate.
	 * @param t The t coordinate.
	 */
	virtual void SetTexCoord(float s, float t);

	/** 
	 * Set material for this object.
	 * 
	 * @param The material.
	 */
	virtual void SetMaterial(aeMaterial *mat);

	/** 
	 * Add a vertex to this object.
	 * This adds a single vertex to this object.
	 * 
	 * @param vertex The vertex vector.
	 */
	virtual void AddVertex(const aeVector3 &vertex);

	/** 
	 * Used to specify whether this object is transparent or not.
	 * 
	 * @param bool true = transparent, false = solid (default).
	 */
	virtual void SetTransparent(bool);

	/** 
	 * Get the number of vertices in this object.
	 * 
	 * 
	 * @return The vertex count of this object.
	 */
	virtual unsigned int GetVertexCount();

	/** 
	 * Get a vertex of this object.
	 * 
	 * @param int The vertex index number.
	 * 
	 * @return The vertex.
	 */
	virtual aeVector3 GetVertex(int);

	/** 
	 * Return the radius of the bounding sphere of this object.
	 * 
	 * 
	 * @return Bounding sphere radius of this object.
	 */
	virtual float GetBoundingSphereRadius();

	/** 
	 * Used to check if this object is currently transparent.
	 * 
	 * 
	 * @return True if the object is transparent, false if not.
	 */
	virtual bool IsTransparent();

	/** 
	 * Set the object rendering mode.
	 * For each derived object type (aeTriangle, aeQuad, aePolygon, aeLine) there is a set of rendering
	 * modes which indicate how the object's vertices are to be interpreted when drawing them.
	 * Possible modes are:
	 * 
	 * <ul>
	 *   <li>TRIANGLES_NORMAL</li>
	 *   <li>TRIANGLES_STRIP</li>
	 *   <li>TRIANGLES_FAN</li>
	 *   <li>QUADS_NORMAL</li>
	 *   <li>QUADS_STRIP</li>
	 *   <li>LINES_NORMAL</li>
	 *   <li>LINES_STRIP</li>
	 *   <li>LINES_LOOP</li>
	 *   <li>POLYGON_NORMAL</li>
	 * </ul>
	 * 
	 * @param mode The object rendering mode to use.
	 * @sa aeObjRenderingMode
	 */
	virtual void SetMode(aeObjRenderingMode mode);
};

#endif // __AELIB_AEGEOM_OBJECT_H__
