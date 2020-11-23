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

#ifndef __AELIB_AEGEOM_VECTOR3_H__
#define __AELIB_AEGEOM_VECTOR3_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD

/** 
 * A 3D vector.
 * 
 */
class aeVector3 {
	AECF_CNDEF

 public:
	/** 
	 * Create a new vector and initialize it to 0, 0, 0.
	 * 
	 */
	aeVector3();

	/** 
	 * Create a new vector and initialize it to x, y, z.
	 * 
	 * @param x The vector's X component.
	 * @param y The vector's Y component.
	 * @param z The vector's Z component.
	 */
	aeVector3(float nx, float ny, float nz = 0) : x(nx), y(ny), z(nz) {}

	/** 
	 * Copy constructor.
	 * 
	 * @param v Vector to copy to this vector.
	 */
	aeVector3(const aeVector3 &v) : x(v.x), y(v.y), z(v.z) {}

	~aeVector3() {};

	/// The X component of the vector.
	float x;
	/// The Y component of the vector.
	float y;
	/// The Z component of the vector.
	float z;

	/** 
	 * Add two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 + Vector2.
	 */
	inline friend aeVector3 operator+(const aeVector3 &v1, const aeVector3 &v2) {
		return aeVector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	/** 
	 * Subtract two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 - Vector2.
	 */
	inline friend aeVector3 operator-(const aeVector3 &v1, const aeVector3 &v2) {
		return aeVector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	/** 
	 * Dot product of two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 . Vector2.
	 */
	inline friend float operator*(const aeVector3 &v1, const aeVector3 &v2) {
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}

	/** 
	 * Cross product of two vectors.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 * 
	 * @return Vector1 X Vector2.
	 */
	inline friend aeVector3 operator%(const aeVector3 &v1, const aeVector3 &v2) {
		return aeVector3((v1.y * v2.z) - (v1.z * v2.y),
						 (v1.z * v2.x) - (v1.x * v2.z),
						 (v1.x * v2.y) - (v1.y * v2.x));
	}

	/** 
	 * Multiply by scalar float.
	 * 
	 * @param v1 Vector.
	 * @param s Scalar float.
	 * 
	 * @return Vector * scalar float.
	 */
	inline friend aeVector3 operator*(const aeVector3 &v1, float s) {
		return aeVector3(v1.x * s, v1.y * s, v1.z * s);
	}

	/** 
	 * Multiply by scalar float.
	 * 
	 * @param s Scalar float.
	 * @param v1 Vector.
	 * 
	 * @return Scalar float * vector.
	 */
	inline friend aeVector3 operator*(float s, const aeVector3 &v1) {
		return aeVector3(v1.x * s, v1.y * s, v1.z * s);
	}

	/** 
	 * Multiply by scalar integer.
	 * 
	 * @param s Scalar integer.
	 * @param v1 Vector.
	 * 
	 * @return Scalar integer * vector
	 */
	inline friend aeVector3 operator*(int s, const aeVector3 &v1) {
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
	inline friend aeVector3 operator/(const aeVector3 &v1, float s) {
		s = 1.0f / s;
		return aeVector3(v1.x * s, v1.y * s, v1.z * s);
	}

	/** 
	 * Divide by scalar integer.
	 * 
	 * @param v1 Vector.
	 * @param s Scalar integer.
	 * 
	 * @return Vector / scalar integer.
	 */
	inline friend aeVector3 operator/(const aeVector3 &v1, int s) {
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
	inline friend bool operator==(const aeVector3 &v1, const aeVector3 &v2) {
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}

	/** 
	 * Check if two vectors are not equal.
	 * 
	 * @param v1 Vector1
	 * @param v2 Vector2
	 * 
	 * @return True if Vector1 != Vector2, false if not.
	 */
	inline friend bool operator!=(const aeVector3 &v1, const aeVector3 &v2) {
		return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
	}

	/** 
	 * Return the Nth component of the vector.
	 * 
	 * @param n The component.
	 * 
	 * @return The Nth component of the vector.
	 */
	inline float operator[](int n) const { return !n ? x : n & 1 ? y : z; }

	/** 
	 * Return the Nth component of the vector.
	 * 
	 * @param n The component.
	 * 
	 * @return The Nth component of the vector.
	 */
	inline float & operator[](int n) { return !n ? x : n & 1 ? y : z; }

	/** 
	 * Add another vector to this vector.
	 * 
	 * @param v1 Vector to add.
	 * 
	 * @return This vector + another vector.
	 */
	inline aeVector3 & operator+=(const aeVector3 &v1) {
		x += v1.x;
		y += v1.y;
		z += v1.z;
		return *this;
	}

	/** 
	 * Subtract another vector from this vector.
	 * 
	 * @param v1 Vector to subtract.
	 * 
	 * @return This vector / another vector.
	 */
	inline aeVector3 & operator-=(const aeVector3 &v1) {
		x -= v1.x;
		y -= v1.y;
		z -= v1.z;
		return *this;
	}

	/** 
	 * Multiply by scalar float.
	 * 
	 * @param s Scalar float
	 * 
	 * @return This vector * scalar float.
	 */
	inline aeVector3 & operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	/** 
	 * Divide by scalar float.
	 * 
	 * @param s Scalar float.
	 * 
	 * @return This vector / scalar float.
	 */
	inline aeVector3 & operator/=(float s) {
		s = 1.0f / s;
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	/** 
	 * Unary +
	 * 
	 * 
	 * @return This vector.
	 */
	inline aeVector3 operator+() const { return *this; }

	/** 
	 * Unary - (negate this vector).
	 * 
	 * 
	 * @return This vector negated.
	 */
	inline aeVector3 operator-() const { return aeVector3(-x, -y, -z); }

	/** 
	 * Set this vector to given x, y, z.
	 * 
	 * @param nx The value to set the x component of this vector to.
	 * @param ny The value to set the y component of this vector to.
	 * @param nz The value to set the z component of this vector to.
	 */
	inline void Set(float nx, float ny, float nz) {
		x = nx;
		y = ny;
		z = nz;
	}

	/** 
	 * Set this vector to another vector.
	 * 
	 * @param v Vector to set this vector to.
	 */
	inline void Set(const aeVector3 &v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	/** 
	 * Get the cross product of two vectors and store the result in this vector.
	 * 
	 * @param v1 Vector1.
	 * @param v2 Vector2.
	 */
	void Cross(const aeVector3 &v1, const aeVector3 &v2);

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
	 * @sa aeVector3::Normalize()
	 * 
	 * @return 
	 */
	aeVector3 Unit() const { return this->Normalize(); }

	/** 
	 * Normalize this vector.
	 * 
	 * 
	 * @return The normalized vector.
	 */
	aeVector3 Normalize() const;
};

#endif // __AELIB_AEGEOM_VECTOR3_H__
