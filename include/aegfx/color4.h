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

#ifndef __AELIB_AEGFX_COLOR4_H__
#define __AELIB_AEGFX_COLOR4_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD

/** 
 * A class representing RGBA color.
 * 
 */
class aeColor4 {
	AECF_CNDEF

 public:
	/** 
	 * Create a new color and initialize it to 1.0, 1.0, 1.0, 1.0 (white, solid).
	 * 
	 */
	aeColor4();

	/** 
	 * Create a new color and initialize it to r, g, b, a.
	 * 
	 * @param r Red.
	 * @param g Green.
	 * @param b Blue.
	 * @param a Alpha.
	 */
	aeColor4(float r, float g, float b, float a);
	~aeColor4();

	/// The red component of this color.
	float red;
	/// The green component of this color.
	float green;
	/// The blue component of this color.
	float blue;
	/// The alpha component of this color.
	float alpha;

	/** 
	 * Set this color to a given RGBA value.
	 * 
	 * @param r Red.
	 * @param g Green.
	 * @param b Blue.
	 * @param a Alpha.
	 */
	void Set(float r, float g, float b, float a);

	/** 
	 * Clamp the color to given RGBA values.
	 * 
	 * @param r Red.
	 * @param g Green.
	 * @param b Blue.
	 * @param a Alpha.
	 */
	void Clamp(float r, float g, float b, float a);

	/** 
	 * Check that color components are not negative
	 * 
	 */
	void ClampDown();

	/** 
	 * Add given RGBA values to this color.
	 * 
	 * @param r Red
	 * @param g Green
	 * @param b Blue
	 * @param a Alpha.
	 */
	void Add(float r, float g, float b, float a);

	/** 
	 * Subtract given RGBA values from this color.
	 * 
	 * @param r Red.
	 * @param g Green.
	 * @param b Blue.
	 * @param a Alpha.
	 */
	void Subtract(float r, float g, float b, float a);

	aeColor4 operator=(aeColor4 c) {
		return aeColor4(red = c.red, green = c.green, blue = c.blue, alpha = c.alpha);
	}

	aeColor4 operator+(aeColor4 c) {
		return aeColor4(red + c.red, green + c.green, blue + c.blue, alpha + c.alpha);
	}

	aeColor4 operator-(aeColor4 c) {
		return aeColor4(red - c.red, green - c.green, blue - c.blue, alpha - c.alpha);
	}
    
	aeColor4 operator*(float num) {
		return aeColor4(red * num, green * num, blue * num, alpha * num);
	}
};

#endif // __AELIB_AEGFX_COLOR4_H__
