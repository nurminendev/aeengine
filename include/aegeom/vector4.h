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

#ifndef __AELIB_AEGEOM_VECTOR4_H__
#define __AELIB_AEGEOM_VECTOR4_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD

/** 
 * A 4D vector.
 * 
 */
class aeVector4 {
	AECF_CNDEF

 public:
	/** 
	 * Create a new vector and initialize it to 0, 0, 0, 1.
	 * 
	 */
	aeVector4();

	/** 
	 * Create a new vector and initialize it to x, y, z, w.
	 * 
	 * @param x The vector's X component.
	 * @param y The vector's Y component.
	 * @param z The vector's Z component.
	 * @param z The vector's W component.
	 */
	aeVector4(float nx, float ny, float nz, float nw = 1) : x(nx), y(ny), z(nz), w(nw) {}

	/** 
	 * Copy constructor.
	 * 
	 * @param v Vector to copy to this vector.
	 */
	aeVector4(const aeVector4 &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	~aeVector4() {};

	/// The X component of the vector.
	float x;
	/// The Y component of the vector.
	float y;
	/// The Z component of the vector.
	float z;
	/// The W component of the vector.
	float w;

	/** 
	 * Add two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 + Vector2.
	 */
	inline friend aeVector4 operator+(const aeVector4 &v1, const aeVector4 &v2) {
		return aeVector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	}

	/** 
	 * Subtract two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 - Vector2.
	 */
	inline friend aeVector4 operator-(const aeVector4 &v1, const aeVector4 &v2) {
		return aeVector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w + v2.w);
	}

	/** 
	 * Dot product of two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 . Vector2.
	 */
	inline friend float operator*(const aeVector4 &v1, const aeVector4 &v2) {
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
	}

	/** 
	 * Cross product of two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 X Vector2.
	 */
	inline friend aeVector4 operator%(const aeVector4 &v1, const aeVector4 &v2) {
		return aeVector4((v1.x * v2.y - v1.y * v2.x) + (v1.x * v2.z - v1.z * v2.x) +
						 (v1.y * v2.z - v1.z * v2.y),
						 (v1.z * v2.y - v1.y * v2.z) + (v1.y * v2.w - v1.w * v2.y) +
						 (v1.z * v2.w - v1.w * v2.z),
						 (v1.x * v2.z - v1.z * v2.x) + (v1.w * v2.x - v1.x * v2.w) +
						 (v1.z * v2.w - v1.w * v2.z),
						 (v1.y * v1.x - v1.x * v2.y) + (v1.w * v2.x - v1.x * v2.w) +
						 (v1.w * v2.y - v1.y * v2.w));
	}

	/** 
	 * Multiply by scalar float.
	 * 
	 * @param v1 Vector.
	 * @param s Scalar float.
	 * 
	 * @return Vector * scalar float.
	 */
	inline friend aeVector4 operator*(const aeVector4 &v1, float s) {
		return aeVector4(v1.x * s, v1.y * s, v1.z * s, v1.w * s);
	}

	/** 
	 * Multiply by scalar float.
	 * 
	 * @param s Scalar float.
	 * @param v1 Vector.
	 * 
	 * @return Scalar float * vector.
	 */
	inline friend aeVector4 operator*(float s, const aeVector4 &v1) {
		return aeVector4(s * v1.x, s * v1.y, s * v1.z, s * v1.w);
	}

	/** 
	 * Multiply by scalar integer.
	 * 
	 * @param v1 Vector.
	 * @param s Scalar integer.
	 * 
	 * @return Scalar integer * vector
	 */
	inline friend aeVector4 operator*(const aeVector4 &v1, int s) {
		return v1 * (float)s;
	}

	/** 
	 * Multiply by scalar integer.
	 * 
	 * @param s Scalar integer.
	 * @param v1 Vector.
	 * 
	 * @return Scalar integer * vector
	 */
	inline friend aeVector4 operator*(int s, const aeVector4 &v1) {
		return (float)s * v1;
	}

	/** 
	 * Divide by scalar float.
	 * 
	 * @param v1 Vector.
	 * @param s Scalar float.
	 * 
	 * @return Vector / scalar float.
	 */
	inline friend aeVector4 operator/(const aeVector4 &v1, float s) {
		s = 1.0f / s;
		return aeVector4(v1.x * s, v1.y * s, v1.z * s, v1.w * s);
	}

	/** 
	 * Divide by scalar integer.
	 * 
	 * @param v1 Vector.
	 * @param s Scalar integer.
	 * 
	 * @return Vector / scalar integer.
	 */
	inline friend aeVector4 operator/(const aeVector4 &v1, int s) {
		return (v1 / (float)s);
	}

	/** 
	 * Check if two vectors are equal.
	 * 
	 * @param v1 Vector1
	 * @param v2 Vector1
	 * 
	 * @return True if Vector1 == Vector2, false if not.
	 */
	inline friend bool operator==(const aeVector4 &v1, const aeVector4 &v2) {
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
	}

	/** 
	 * Check if two vectors are not equal.
	 * 
	 * @param v1 Vector1
	 * @param v2 Vector2
	 * 
	 * @return True if Vector1 != Vector2, false if not.
	 */
	inline friend bool operator!=(const aeVector4 &v1, const aeVector4 &v2) {
		return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
	}

	/** 
	 * Return the Nth component of the vector.
	 * 
	 * @param n The component.
	 * 
	 * @return The Nth component of the vector.
	 */
	inline float operator[](int n) const { return !n ? x : n & 1 ? y : n & 2 ? z : w; }

	/** 
	 * Return the Nth component of the vector.
	 * 
	 * @param n The component.
	 * 
	 * @return The Nth component of the vector.
	 */
	inline float & operator[](int n) { return !n ? x : n & 1 ? y : n & 2 ? z : w; }

	/** 
	 * Add another vector to this vector.
	 * 
	 * @param v1 Vector to add.
	 * 
	 * @return This vector + another vector.
	 */
	inline aeVector4 & operator+=(const aeVector4 &v1) {
		x += v1.x;
		y += v1.y;
		z += v1.z;
		w += v1.w;
		return *this;
	}

	/** 
	 * Subtract another vector from this vector.
	 * 
	 * @param v1 Vector to subtract.
	 * 
	 * @return This vector / another vector.
	 */
	inline aeVector4 & operator-=(const aeVector4 &v1) {
		x -= v1.x;
		y -= v1.y;
		z -= v1.z;
		w -= v1.w;
		return *this;
	}

	/** 
	 * Multiply by scalar float.
	 * 
	 * @param s Scalar float
	 * 
	 * @return This vector * scalar float.
	 */
	inline aeVector4 & operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	/** 
	 * Divide by scalar float.
	 * 
	 * @param s Scalar float.
	 * 
	 * @return This vector / scalar float.
	 */
	inline aeVector4 & operator/=(float s) {
		s = 1.0f / s;
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	/** 
	 * Unary +
	 * 
	 * 
	 * @return This vector.
	 */
	inline aeVector4 operator+() const { return *this; }

	/** 
	 * Unary - (negate this vector).
	 * 
	 * 
	 * @return This vector negated.
	 */
	inline aeVector4 operator-() const { return aeVector4(-x, -y, -z, -w); }

	/** 
	 * Set this vector to given x, y, z, w.
	 * 
	 * @param nx The value to set the x component of this vector to.
	 * @param ny The value to set the y component of this vector to.
	 * @param nz The value to set the z component of this vector to.
	 * @param nw The value to set the w component of this vector to.
	 */
	inline void Set(float nx, float ny, float nz, float nw) {
		x = nx;
		y = ny;
		z = nz;
		w = nw;
	}

	/** 
	 * Set this vector to another vector.
	 * 
	 * @param v Vector to set this vector to.
	 */
	inline void Set(const aeVector4 &v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	/** 
	 * Get the cross product of two vectors and store the result in this vector.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 */
	void Cross(const aeVector4 &v1, const aeVector4 &v2);

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
	 * @sa aeVector4::Normalize()
	 * 
	 * @return 
	 */
	aeVector4 Unit() const { return this->Normalize(); }

	/** 
	 * Normalize this vector.
	 * 
	 * 
	 * @return The normalized vector.
	 */
	aeVector4 Normalize() const;
};

#endif // __AELIB_AEGEOM_VECTOR4_H__
