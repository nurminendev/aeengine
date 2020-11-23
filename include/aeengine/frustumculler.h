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

#ifndef __AELIB_AEENGINE_FRUSTUMCULLER_H__
#define __AELIB_AEENGINE_FRUSTUMCULLER_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aegeom/vector3.h>
#include <aereg/base.h>

/** 
 * Engine level Interface to the frustum culler
 * 
 */
class aeFrustumCuller: public aeBase {
	AECF_CNDEF

 private:
	float frustum[6][4];

 public:
	aeFrustumCuller();
	~aeFrustumCuller();

	/** 
	 * Extract the current view-frustum. This is called each frame by the engine rendering loop.
	 * 
	 */
	void ExtractFrustum();

	/** 
	 * Check if a point is in the frustum.
	 * 
	 * @param point The point (vertex) to check.
	 * 
	 * @return True if the point is currently visible by the camera, false if not.
	 */
	bool PointInFrustum(aeVector3 point);

	/** 
	 * Check if an object's bounding sphere is in the frustum.
	 * 
	 * @param center The origin of the object to check.
	 * @param radius The bounding sphere radius of the object.
	 * 
	 * @return True if the object's bounding sphere is visible by the camera, false if not.
	 */
	bool SphereInFrustum(aeVector3 center, float radius);

	/** 
	 * Check if an object's bounding box is in the frustum.
	 * 
	 * @param center The origin of the object to check.
	 * @param size The bounding box size (half of the cube's length).
	 * 
	 * @return True if the object's bounding box is visible by the camera, false if not.
	 */
	bool CubeInFrustum(aeVector3 center, float size);
};

#endif // __AELIB_AEENGINE_FRUSTUMCULLER_H__
