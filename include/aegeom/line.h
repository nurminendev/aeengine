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

#ifndef __AELIB_AEGEOM_LINE_H__
#define __AELIB_AEGEOM_LINE_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aeengine/eflags.h>
#include <aegeom/object.h>

/** 
 * A 3D line.
 * 
 */
class aeLine: public aeObject {
	AECF_CNDEF

 public:
	/** 
	 * Create a new line object with no name.
	 * Naturally you won't be able to find the line from the engine by its name.
	 * 
	 */
	aeLine();

	/** 
	 * Create a new line object given a name.
	 * Use this if you want to find the object from the objectpool at later time.
	 * 
	 * @param char * The object name.
	 * 
	 * @sa aeRegistry::FindObjectByName()
	 */
	aeLine(char *);
	virtual ~aeLine();

	/** 
	 * Draw the line. After you have added the object to the engine's objectpool,
	 * aeEngine::Render() (which you should call upon aeevProcessFrame event) will
	 * call this method to draw the object. You should not need to call this yourself.
	 * 
	 * @sa aeEngine::AddObject(), aeEngine::Render()
	 */
	void Draw(aeEngineflags *);
};

#endif // __AELIB_AEGEOM_LINE_H__
