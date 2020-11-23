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

#ifndef __AELIB_AEENGINE_EFLAGS_H__
#define __AELIB_AEENGINE_EFLAGS_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD

/// Engine flags structure.
struct aeEngineflags {
	/// True if multitexturing is supported
	bool hasMultitexture;
	/// Use multipass rendering or not.
	/*!
	 * If multitexturing is not supported, this flag indicates whether to use
	 * multipass multitexturing (true) or completely disable multitexturing (false).
	 * It's set to true by default.
	 */
	bool doMultipass;
	/// Number of texture units.
	int texUnits;
};

#endif // __AELIB_AEENGINE_EFLAGS_H__
