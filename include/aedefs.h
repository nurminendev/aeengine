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

#ifndef __AE_AEDEFS_H__
#define __AE_AEDEFS_H__

#ifdef WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  undef WIN32_LEAN_AND_MEAN
#  define ISWIN32 1
#else
#  define ISWIN32 0
#endif

#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <map>

// Define ONLY_INCLUDE_STD before including this file if you don't need the
// video stuff included but only the std includes (and aetypes.h).
#ifndef ONLY_INCLUDE_STD
#include <GL/gl.h>
#include <GL/glu.h>
#include <glext.h>
#include <SDL.h>
#endif

#include <aetypes.h>

#if !defined(ONLY_INCLUDE_STD) && defined(WIN32) && defined(_MSC_VER)
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL.lib")
#endif

#ifndef AE_APPLICATION
#define AE_APPLICATION aeMemoryManager memmgr(6, 128);
#endif

#define AECF_CN_MAXLEN 16
#define AECF_CNDEF protected: char _aemm_clname[AECF_CN_MAXLEN + 8];
#define AECF_CNAME(name) \
 _aemm_clname[0]=0x51; \
 _aemm_clname[1]=0x50; \
 _aemm_clname[2]='<'; \
 _aemm_clname[3]='<'; \
 int offset = 4; \
 while(name[offset - 4] != 0) { \
     _aemm_clname[offset] = name[(offset++) - 4]; \
 } \
 while(offset < AECF_CN_MAXLEN + 4) { \
     _aemm_clname[offset++] = '_'; \
 } \
 _aemm_clname[offset++] = '>'; \
 _aemm_clname[offset++] = '>'; \
 _aemm_clname[offset++] = 0x50; \
 _aemm_clname[offset++] = 0x51;

/** @defgroupt aeglobalops Global AE Operators.
 * Varius globally-overwritten operators.
 * @{
 */

/// aeMemoryManager: Overwritten global new operator.
/*!
 * It registers 'blockdescriptors' via a static method in an allocator-instance.
 * 
 */
void *operator new(size_t size, const char* filename, int line);
/// aeMemoryManager: Overwritten global new[] operator.
/*!
 * It registers 'blockdescriptors' via a static method in an allocator-instance.
 * 
 */
void *operator new[](size_t size, const char* filename, int line);

/// aeMemoryManager: Overwritten global delete operator.
/*!
 * It de-registers 'blockdescriptors' via a static method in an allocator-instance.
 * 
 */
void operator delete(void *pblock);

/// aeMemoryManager: Overwritten global delete[] operator.
/*!
 * It de-registers 'blockdescriptors' via a static method in an allocator-instance.
 * 
 */
void operator delete[](void *pblock);

/** @} */

// conflict with the actual overriding-procedure (it'll insert this macro's
// expansion into the source of overriding ... not working very well ;-) )
// "hacking" it this way it stays the same include-file for both, application
// and the memmanager.o - objectfile.
#ifndef __AE_MEMORYMANAGER_CPP__
#define new new(__FILE__, __LINE__)
#endif

#endif // __AE_AEDEFS_H__
