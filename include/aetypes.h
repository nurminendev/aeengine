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

#ifndef __AE_AETYPES_H__
#define __AE_AETYPES_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD

/** @defgroup aetypedefs AE typedefs
 * Varius typedeffings.
 * @{
 */

/// Unsigned 1-byte integer.
typedef unsigned char uint8;
/// Signed 1-byte integer.
typedef signed char sint8;
/// Unsigned 2-byte integer.
typedef unsigned short uint16;
/// Signed 2-byte integer.
typedef signed short sint16;
/// Unsigned 4-byte integer.
typedef unsigned int uint32;
/// Signed 4-byte integer.
typedef signed int sint32;

class aeBlockDescriptor;
class aeVector3;
class aeTexCoord2;
class aeColor4;

/// This map maps pointers to blockdescriptors.
typedef std::map<void*, aeBlockDescriptor*> aeBlockDescriptor_map;

/// This vector contains aeVector3 instances.
typedef std::vector<aeVector3> aeVector3_vector;

/// This vector contains aeTexCoord2 instances.
typedef std::vector<aeTexCoord2> aeTexCoord2_vector;

/// This vector contains aeColor4 instances.
typedef std::vector<aeColor4> aeColor4_vector;

/** @} */

#endif // __AE_AETYPES_H__
