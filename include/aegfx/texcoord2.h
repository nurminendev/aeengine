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

#ifndef __AELIB_AEGFX_TEXCOORD2_H__
#define __AELIB_AEGFX_TEXCOORD2_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD

/** 
 * A class representing single 2D texture coordinate.
 * 
 */
class aeTexCoord2 {
	AECF_CNDEF

 public:
	/** 
	 * Create a new texture coordinate and initialize it to 0, 0.
	 * 
	 */
	aeTexCoord2() {};

	/** 
	 * Create a new texture coordinate and initialize it to s, t.
	 * 
	 * @param s The texcoords's S component.
	 * @param t The texcoords's T component.
	 */
	aeTexCoord2(float ns, float nt = 0) : s(ns), t(nt) {}

	/** 
	 * Copy constructor.
	 * 
	 * @param t Texcoord to copy to this texcoord.
	 */
	aeTexCoord2(const aeTexCoord2 &tc) : s(tc.s), t(tc.t) {}

	~aeTexCoord2() {};

	/// The S component of the texture coordinate.
	float s;
	/// The T component of the texture coordinate.
	float t;

	/** 
	 * Check if two texcoords are equal.
	 * 
	 * @param t1 Texcoord1
	 * @param t2 Texcoord2
	 * 
	 * @return True if Texcoord1 == Texcoord2, false if not.
	 */
	inline friend bool operator==(const aeTexCoord2 &t1, const aeTexCoord2 &t2) {
		return t1.s == t2.s && t1.t == t2.t;
	}

	/** 
	 * Check if two texcoords are not equal.
	 * 
	 * @param t1 Texcoord1
	 * @param t2 Texcoord2
	 * 
	 * @return True if Texcoord1 != Texcoord2, false if not.
	 */
	inline friend bool operator!=(const aeTexCoord2 &t1, const aeTexCoord2 &t2) {
		return t1.s != t2.s || t1.t != t2.t;
	}

	/** 
	 * Set this texcoord to given s, t.
	 * 
	 * @param ns The value to set the s component of this texcoord to.
	 * @param nt The value to set the t component of this texcoord to.
	 */
	inline void Set(float ns, float nt) {
		s = ns;
		t = nt;
	}

	/** 
	 * Set this texcoord to another texcoord.
	 * 
	 * @param t Texcoord to set this texcoord to.
	 */
	inline void Set(const aeTexCoord2 &tc) {
		s = tc.s;
		t = tc.t;
	}
};

#endif // __AELIB_AEGFX_TEXCOORD_H__
