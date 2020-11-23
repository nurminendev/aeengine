/*
 *  AE Engine
 *
 *  Copyright (C) 2003 Riku "Rakkis" Nurminen
 *
 *  This memory manager originally contributed by swente <ssuebert@web.de>
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

#ifndef __AELIB_AEMM_BLOCKDESCRIPTOR_H__
#define __AELIB_AEMM_BLOCKDESCRIPTOR_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD

/** 
 * This class describes allocated memory-chunks.
 * On its own destruction, it does *not* free the memory-block it describes.
 * 
 */
class aeBlockDescriptor {
 public:
	aeBlockDescriptor(void *addr, size_t size, const char *filename, int linenumber);
	~aeBlockDescriptor();

	void *m_addr;
	size_t m_size;
	char *m_pfilename;
	int m_linenumber;
};

#endif // __AELIB_AEMM_BLOCKDESCRIPTOR_H__
