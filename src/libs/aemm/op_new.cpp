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

#define ONLY_INCLUDE_STD
#define __AE_MEMORYMANAGER_CPP__
#include <aedefs.h>
#undef __AE_MEMORYMANAGER_CPP__
#undef ONLY_INCLUDE_STD
#include <aemm/memorymanager.h>

// new
void *operator new(size_t s, const char *filename, int line)
{
	void *block = malloc(s);
	aeMemoryManager::Registerblock(block, s, filename, line);
	return block;
}

// new[]
void *operator new[](size_t s, const char* filename, int line)
{
	void *block = malloc(s);
	aeMemoryManager::Registerblock(block, s, filename, line);
	return block;
}
