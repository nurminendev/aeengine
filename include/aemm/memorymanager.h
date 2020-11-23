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

#ifndef __AELIB_AEMM_MEMORYMANAGER_H__
#define __AELIB_AEMM_MEMORYMANAGER_H__

#include <aedefs.h>
#include <aereg/base.h>

/** 
 * The AE memory manager.
 * 
 */
class aeMemoryManager: public aeBase {
 private:
	/// Static global self ref.
	static aeMemoryManager *pglob_self;
	/// Map containing the blockdescriptors.
	aeBlockDescriptor_map m_blockdescriptormap;
	/// Dump-output: column is 4 bytes.
	int m_blocks;
	/// Dump-output: max. amount of bytes to dump
	int m_maxdumpbytes;

 public:
	/** 
	 * Memory manager constructor.
	 * 
	 * @param blocks Indicates how many 4-byte columns should the output dump have.
	 * @param maxdumpbytes Maximum bytes to dump. Defaults to 256.
	 * 
	 * @return 
	 */
	aeMemoryManager(int blocks, int maxdumpbytes = 256);

	~aeMemoryManager();

	/** 
	 * Static method: called from overloaded "new"-operator.
	 * It creates a new descriptor and registers it in
	 * the memmanager referenced by it's global selfptr.
	 * 
	 */
	static void Registerblock(void *addr, size_t size, const char *filename, int linenumber);

	/** 
	 * Static method: called from overloaded "delete"-operator.
	 * It searches for a machting descriptor in the memmanager
	 * pointed to by it's global self-ref, unregisters it and
	 * deletes it.
	 * 
	 */
	static void Unregisterblock(void *addr);
};

#endif // __AELIB_AEMM_MEMORYMANAGER_H__
