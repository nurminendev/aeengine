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

#ifndef __AELIB_AEGEOM_VECTOR_H__
#define __AELIB_AEGEOM_VECTOR_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD

/** 
 * A 2D vector.
 * 
 */
class aeVector {
	AECF_CNDEF

 public:
	/** 
	 * Create a new vector and initialize it to 0, 0.
	 * 
	 */
	aeVector();

	/** 
	 * Create a new vector and initialize it to x, y.
	 * 
	 * @param x The vector's X component.
	 * @param y The vector's Y component.
	 */
	aeVector(float nx, float ny = 0) : x(nx), y(ny) {}

	/** 
	 * Copy constructor.
	 * 
	 * @param v Vector to copy to this vector.
	 */
	aeVector(const aeVector &v) : x(v.x), y(v.y) {}

	~aeVector() {};

	/// The X component of the vector.
	float x;
	/// The Y component of the vector.
	float y;

	/** 
	 * Add two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 + Vector2.
	 */
	inline friend aeVector operator+(const aeVector &v1, const aeVector &v2) {
		return aeVector(v1.x + v2.x, v1.y + v2.y);
	}

	/** 
	 * Subtract two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 - Vector2.
	 */
	inline friend aeVector operator-(const aeVector &v1, const aeVector &v2) {
		return aeVector(v1.x - v2.x, v1.y - v2.y);
	}

	/** 
	 * Dot product of two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 . Vector2.
	 */
	inline friend float operator*(const aeVector &v1, const aeVector &v2) {
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	/** 
	 * Multiply by scalar float.
	 * 
	 * @param v1 Vector.
	 * @param s Scalar float.
	 * 
	 * @return Vector * scalar float.
	 */
	inline friend aeVector operator*(const aeVector &v1, float s) {
		return aeVector(v1.x * s, v1.y * s);
	}

	/** 
	 * Multiply by scalar float.
	 * 
	 * @param s Scalar float.
	 * @param v1 Vector.
	 * 
	 * @return Scalar float * vector.
	 */
	inline friend aeVector operator*(float s, const aeVector &v1) {
		return aeVector(v1.x * s, v1.y * s);
	}

	/** 
	 * Multiply by scalar integer.
	 * 
	 * @param s Scalar integer.
	 * @param v1 Vector.
	 * 
	 * @return Scalar integer * vector
	 */
	inline friend aeVector operator*(int s, const aeVector &v1) {
		return v1 * (float)s;
	}

	/** 
	 * Divide by scalar float.
	 * 
	 * @param v1 Vector.
	 * @param s Scalar float.
	 * 
	 * @return Vector / scalar float.
	 */
	inline friend aeVector operator/(const aeVector &v1, float s) {
		s = 1.0f / s;
		return aeVector(v1.x * s, v1.y * s);
	}

	/** 
	 * Divide by scalar integer.
	 * 
	 * @param v1 Vector.
	 * @param s Scalar integer.
	 * 
	 * @return Vector / scalar integer.
	 */
	inline friend aeVector operator/(const aeVector &v1, int s) {
		return (v1 / (float)s);
	}

	/** 
	 * Check if two vectors are equal.
	 * 
	 * @param v1 Vector1
	 * @param v2 Vector2
	 * 
	 * @return True if Vector1 == Vector2, false if not.
	 */
	inline friend bool operator==(const aeVector &v1, const aeVector &v2) {
		return v1.x == v2.x && v1.y == v2.y;
	}

	/** 
	 * Check if two vectors are not equal.
	 * 
	 * @param v1 Vector1
	 * @param v2 Vector2
	 * 
	 * @return True if Vector1 != Vector2, false if not.
	 */
	inline friend bool operator!=(const aeVector &v1, const aeVector &v2) {
		return v1.x != v2.x || v1.y != v2.y;
	}

	/** 
	 * Add another vector to this vector.
	 * 
	 * @param v1 Vector to add.
	 * 
	 * @return This vector + another vector.
	 */
	inline aeVector & operator+=(const aeVector &v1) {
		x += v1.x;
		y += v1.y;
		return *this;
	}

	/** 
	 * Subtract another vector from this vector.
	 * 
	 * @param v1 Vector to subtract.
	 * 
	 * @return This vector / another vector.
	 */
	inline aeVector & operator-=(const aeVector &v1) {
		x -= v1.x;
		y -= v1.y;
		return *this;
	}

	/** 
	 * Multiply by scalar float.
	 * 
	 * @param s Scalar float
	 * 
	 * @return This vector * scalar float.
	 */
	inline aeVector & operator*=(float s) {
		x *= s;
		y *= s;
		return *this;
	}

	/** 
	 * Divide by scalar float.
	 * 
	 * @param s Scalar float.
	 * 
	 * @return This vector / scalar float.
	 */
	inline aeVector & operator/=(float s) {
		s = 1.0f / s;
		x *= s;
		y *= s;
		return *this;
	}

	/** 
	 * Unary +
	 * 
	 * 
	 * @return This vector.
	 */
	inline aeVector operator+() const { return *this; }

	/** 
	 * Unary - (negate this vector).
	 * 
	 * 
	 * @return This vector negated.
	 */
	inline aeVector operator-() const { return aeVector(-x, -y); }

	/** 
	 * Set this vector to given x, y.
	 * 
	 * @param nx The value to set the x component of this vector to.
	 * @param ny The value to set the y component of this vector to.
	 */
	inline void Set(float nx, float ny) {
		x = nx;
		y = ny;
	}

	/** 
	 * Set this vector to another vector.
	 * 
	 * @param v Vector to set this vector to.
	 */
	inline void Set(const aeVector &v) {
		x = v.x;
		y = v.y;
	}

	/** 
	 * Get the cross product of two vectors and store the result in this vector.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 */
	aeVector Cross(const aeVector &v1, const aeVector &v2);

	/** 
	 * Get the magnitude (lenght) of this vector.
	 * 
	 * 
	 * @return The vector's magnitude.
	 */
	float Magnitude() const;

	/** 
	 * Get the unit vector of this vector. This is essentialy the same as Normalize().
	 * 
	 * @sa aeVector::Normalize()
	 * 
	 * @return 
	 */
	aeVector Unit() const { return this->Normalize(); }

	/** 
	 * Normalize this vector.
	 * 
	 * 
	 * @return The normalized vector.
	 */
	aeVector Normalize() const;
};

#endif // __AELIB_AEGEOM_VECTOR_H__
