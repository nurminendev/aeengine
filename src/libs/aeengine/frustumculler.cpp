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

#include <aedefs.h>
#include <aeengine/frustumculler.h>
#include <aegeom/vector3.h>

aeFrustumCuller::aeFrustumCuller()
{
	AECF_CNAME("aeFrustumCuller")
}

aeFrustumCuller::~aeFrustumCuller()
{
}

void aeFrustumCuller::ExtractFrustum()
{
	float proj[16];
	float modl[16];
	float clip[16];
	float t;

	glGetFloatv(GL_PROJECTION_MATRIX, proj); // Get the current projection matrix
	glGetFloatv(GL_MODELVIEW_MATRIX, modl); // Get the current modelview matrix

	// Combine the two matrices (multiply projection by modelview)
	clip[0] = modl[0] * proj[0] + modl[1] * proj[4] + modl[2] * proj[8] + modl[3] * proj[12];
	clip[1] = modl[0] * proj[1] + modl[1] * proj[5] + modl[2] * proj[9] + modl[3] * proj[13];
	clip[2] = modl[0] * proj[2] + modl[1] * proj[6] + modl[2] * proj[10] + modl[3] * proj[14];
	clip[3] = modl[0] * proj[3] + modl[1] * proj[7] + modl[2] * proj[11] + modl[3] * proj[15];

	clip[4] = modl[4] * proj[0] + modl[5] * proj[4] + modl[6] * proj[8] + modl[7] * proj[12];
	clip[5] = modl[4] * proj[1] + modl[5] * proj[5] + modl[6] * proj[9] + modl[7] * proj[13];
	clip[6] = modl[4] * proj[2] + modl[5] * proj[6] + modl[6] * proj[10] + modl[7] * proj[14];
	clip[7] = modl[4] * proj[3] + modl[5] * proj[7] + modl[6] * proj[11] + modl[7] * proj[15];

	clip[8] = modl[8] * proj[0] + modl[9] * proj[4] + modl[10] * proj[8] + modl[11] * proj[12];
	clip[9] = modl[8] * proj[1] + modl[9] * proj[5] + modl[10] * proj[9] + modl[11] * proj[13];
	clip[10] = modl[8] * proj[2] + modl[9] * proj[6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[8] * proj[3] + modl[9] * proj[7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[0] + modl[13] * proj[4] + modl[14] * proj[8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[1] + modl[13] * proj[5] + modl[14] * proj[9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[2] + modl[13] * proj[6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[3] + modl[13] * proj[7] + modl[14] * proj[11] + modl[15] * proj[15];

    // Extract the numbers for the right plane
	frustum[0][0] = clip[3] - clip[0];
	frustum[0][1] = clip[7] - clip[4];
	frustum[0][2] = clip[11] - clip[8];
	frustum[0][3] = clip[15] - clip[12];

	// Normalize the result
	t = sqrt(frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2]);
	frustum[0][0] /= t;
	frustum[0][1] /= t;
	frustum[0][2] /= t;
	frustum[0][3] /= t;

	// Extract the numbers for the left plane
	frustum[1][0] = clip[3] + clip[0];
	frustum[1][1] = clip[7] + clip[4];
	frustum[1][2] = clip[11] + clip[8];
	frustum[1][3] = clip[15] + clip[12];

	// Normalize the result
	t = sqrt(frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2]);
	frustum[1][0] /= t;
	frustum[1][1] /= t;
	frustum[1][2] /= t;
	frustum[1][3] /= t;

	// Extract the bottom plane
	frustum[2][0] = clip[3] + clip[1];
	frustum[2][1] = clip[7] + clip[5];
	frustum[2][2] = clip[11] + clip[9];
	frustum[2][3] = clip[15] + clip[13];

	// Normalize the result
	t = sqrt(frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2]);
	frustum[2][0] /= t;
	frustum[2][1] /= t;
	frustum[2][2] /= t;
	frustum[2][3] /= t;

	// Extract the top plane
	frustum[3][0] = clip[3] - clip[1];
	frustum[3][1] = clip[7] - clip[5];
	frustum[3][2] = clip[11] - clip[9];
	frustum[3][3] = clip[15] - clip[13];

	// Normalize the result
	t = sqrt(frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2]);
	frustum[3][0] /= t;
	frustum[3][1] /= t;
	frustum[3][2] /= t;
	frustum[3][3] /= t;

	// Extract the far plane
	frustum[4][0] = clip[3] - clip[2];
	frustum[4][1] = clip[7] - clip[6];
	frustum[4][2] = clip[11] - clip[10];
	frustum[4][3] = clip[15] - clip[14];

	// Normalize the result
	t = sqrt(frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2]);
	frustum[4][0] /= t;
	frustum[4][1] /= t;
	frustum[4][2] /= t;
	frustum[4][3] /= t;

	// Extract the near plane
	frustum[5][0] = clip[3] + clip[2];
	frustum[5][1] = clip[7] + clip[6];
	frustum[5][2] = clip[11] + clip[10];
	frustum[5][3] = clip[15] + clip[14];

	// Normalize the result
	t = sqrt(frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2]);
	frustum[5][0] /= t;
	frustum[5][1] /= t;
	frustum[5][2] /= t;
	frustum[5][3] /= t;
}

bool aeFrustumCuller::PointInFrustum(aeVector3 point)
{
	int p;

    for(p = 0; p < 6; p++) {
		if(frustum[p][0] * point.x +
		   frustum[p][1] * point.y +
		   frustum[p][2] * point.z +
		   frustum[p][3] <= 0) {
			return false;
		}
	}

	return true;
}

bool aeFrustumCuller::SphereInFrustum(aeVector3 center, float radius)
{
	unsigned int p;

	for(p = 0; p < 6; p++)
		if(frustum[p][0] * center.x +
		   frustum[p][1] * center.y +
		   frustum[p][2] * center.z +
		   frustum[p][3] <= -radius)
			return false;

	return true;
}

bool aeFrustumCuller::CubeInFrustum(aeVector3 center, float size)
{
	int p;

	for(p = 0; p < 6; p++) {
		if(frustum[p][0] * (center.x - size) + frustum[p][1] * (center.y - size) + 
		   frustum[p][2] * (center.z - size) + frustum[p][3] > 0)
			continue;
		if(frustum[p][0] * (center.x + size) + frustum[p][1] * (center.y - size) +
		   frustum[p][2] * (center.z - size) + frustum[p][3] > 0)
			continue;
		if(frustum[p][0] * (center.x - size) + frustum[p][1] * (center.y + size) +
		   frustum[p][2] * (center.z - size) + frustum[p][3] > 0)
			continue;
		if(frustum[p][0] * (center.x + size) + frustum[p][1] * (center.y + size) +
		   frustum[p][2] * (center.z - size) + frustum[p][3] > 0)
			continue;
		if(frustum[p][0] * (center.x - size) + frustum[p][1] * (center.y - size) +
		   frustum[p][2] * (center.z + size) + frustum[p][3] > 0)
			continue;
		if(frustum[p][0] * (center.x + size) + frustum[p][1] * (center.y - size) +
		   frustum[p][2] * (center.z + size) + frustum[p][3] > 0)
			continue;
		if(frustum[p][0] * (center.x - size) + frustum[p][1] * (center.y + size) +
		   frustum[p][2] * (center.z + size) + frustum[p][3] > 0)
			continue;
		if(frustum[p][0] * (center.x + size) + frustum[p][1] * (center.y + size) +
		   frustum[p][2] * (center.z + size) + frustum[p][3] > 0)
			continue;
		return false;
	}
	return true;
}
