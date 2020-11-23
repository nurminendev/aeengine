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

#ifndef __AELIB_AEUTIL_UTIL_H__
#define __AELIB_AEUTIL_UTIL_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aegeom/vector3.h>

/** 
 * General static utility functions.
 */
class aeUtil {
 public:
	/** 
	 * Report (print) text into the console.
	 * Formatting of message works just like in printf() etc. Use this for debugging or whatever
	 * printing you need to do (to the console).
	 * 
	 * @param const char * Where from the message comes (e.g. "ae.engine.Render").
	 * @param const char * The message to print.
	 * @param ... Any modifiers
	 */
	static void Report(const char *, const char *, ...);

	/** 
	 * Checks if a string is included in another string.
	 * 
	 * @param searchstr String to search for.
	 * @param str String to search from.
	 * 
	 * @return 
	 */
	static bool aeUtil::InStr(char *searchstr, char *str);

	/** 
	 * Calculate normal for a triangle.
	 * 
	 * @param aeVector3 & First vertex of triangle.
	 * @param  aeVector3 & Second vertex of triangle.
	 * @param  aeVector3 & Third vertex of triangle.
	 * 
	 * @return Calculated normal for the triangle.
	 */
	static aeVector3 CalculateNormal(const aeVector3 &v1, const aeVector3 &v2, const aeVector3 &v3);
};

#endif // __AELIB_AEUTIL_UTIL_H__
