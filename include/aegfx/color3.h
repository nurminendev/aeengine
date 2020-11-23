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

#ifndef __AELIB_AEGFX_COLOR3_H__
#define __AELIB_AEGFX_COLOR3_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD

/**
 * A class representing RGB color.
 * 
 */
class aeColor3 {
	AECF_CNDEF

 public:
	/** 
	 * Create a new color and initialize it to 1.0, 1.0, 1.0 (white).
	 * 
	 */
	aeColor3();

	/** 
	 * Create a new color and initialize it to r, g, b.
	 * 
	 * @param r Red.
	 * @param g Green.
	 * @param b Blue.
	 */	aeColor3(float r, float g, float b);
	~aeColor3();

	/// The red component of this color.
	float red;
	/// The green component of this color.
	float green;
	/// The blue component of this color.
	float blue;

	/** 
	 * Set this color to a given RGB value.
	 * 
	 * @param r Red.
	 * @param g Green.
	 * @param b Blue.
	 */
	void Set(float r, float g, float b);

	/** 
	 * Clamp the color to given RGB values.
	 * 
	 * @param r Red.
	 * @param g Green.
	 * @param b Blue.
	 */
	void Clamp(float r, float g, float b);

	/** 
	 * Check that color components are not negative
	 * 
	 */
	void ClampDown();

	/** 
	 * Add given RGB values to this color.
	 * 
	 * @param r Red
	 * @param g Green
	 * @param b Blue
	 */
	void Add(float r, float g, float b);

	/** 
	 * Subtract given RGB values from this color.
	 * 
	 * @param r Red.
	 * @param g Green.
	 * @param b Blue.
	 */
	void Subtract(float r, float g, float b);

	aeColor3 operator=(aeColor3 c) {
		return aeColor3(red = c.red, green = c.green, blue = c.blue);
	}

	aeColor3 operator+(aeColor3 c) {
		return aeColor3(red + c.red, green + c.green, blue + c.blue);
	}

	aeColor3 operator-(aeColor3 c) {
		return aeColor3(red - c.red, green - c.green, blue - c.blue);
	}
    
	aeColor3 operator*(float num) {
		return aeColor3(red * num, green * num, blue * num);
	}
};

#endif // __AELIB_AEGFX_COLOR3_H__
