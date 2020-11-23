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

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aegeom/vector3.h>

aeVector3::aeVector3()
{
	AECF_CNAME("aeVector3")
}

void aeVector3::Cross(const aeVector3 &v1, const aeVector3 &v2)
{
	x = (v1.y * v2.z) - (v1.z * v2.y);
	y = (v1.z * v2.x) - (v1.x * v2.z);
	z = (v1.x * v2.y) - (v1.y * v2.x);
}

float aeVector3::Magnitude() const
{
	return (float)sqrt((x * x) + (y * y) + (z * z));
}

aeVector3 aeVector3::Normalize() const
{
	return (*this) / (this->Magnitude());
}
