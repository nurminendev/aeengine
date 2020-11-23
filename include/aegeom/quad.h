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

#ifndef __AELIB_AEGEOM_QUAD_H__
#define __AELIB_AEGEOM_QUAD_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aeengine/eflags.h>
#include <aegeom/object.h>

/** 
 * A 3D quad.
 * 
 */
class aeQuad: public aeObject {
	AECF_CNDEF

 public:
	/** 
	 * Create a quad with no name.
	 * Naturally you won't be able to find this object from the engine by name.
	 * 
	 */
	aeQuad();

	/** 
	 * Create a quad given a name.
	 * 
	 * @param char * The quad's name.
	 */
	aeQuad(char *);
	virtual ~aeQuad();

	/** 
	 * Draw the quad. This is called by aeEngine::Render(). You shouldn't need to call this
	 * yourself.
	 * 
	 */
	void Draw(aeEngineflags *);
};

#endif // __AELIB_AEGEOM_QUAD_H__
