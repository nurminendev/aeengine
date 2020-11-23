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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#define ONLY_INCLUDE_STD
#define __AE_MEMORYMANAGER_CPP__
#include <aedefs.h>
#undef __AE_MEMORYMANAGER_CPP__
#undef ONLY_INCLUDE_STD
#include <aemm/blockdescriptor.h>
#include <aemm/memorymanager.h>
#include <aeutil/util.h>

aeMemoryManager *aeMemoryManager::pglob_self = NULL;

aeMemoryManager::aeMemoryManager(int blocks, int maxdumpbytes)
{
	m_blocks = blocks;
	m_maxdumpbytes = maxdumpbytes;

	// just one instance allowed
	if(pglob_self != NULL) {
		Report(0, "*** INSTANTIATING A SECOND aeMemoryManager!\n");
	}

	// static global selfref
	pglob_self = this;
}

aeMemoryManager::~aeMemoryManager()
{
	// Destructor:
	// All in all it just "dumps" all stale objects - it does not even delete them, as
	// stale objects are usually a result of logical errors in the program.
	// /me would not take the responsibility for deleting objects ...

	Report(0, "*** results: %d objects leaked ***\n", m_blockdescriptormap.size());

	// iterate once over all blockdescriptors just for finding the longes filename
	int max_namelen = 0;
	for(aeBlockDescriptor_map::iterator x = m_blockdescriptormap.begin(); x != m_blockdescriptormap.end(); ++x) {

		// those two vars get their value from iterator
		void *pBlock = x->first;
		aeBlockDescriptor *pBlockdescriptor = x->second;

		// valid ? strange things seem to happen
		if(pBlockdescriptor == NULL) {
			Report(0, "*** PROBLEM: no descriptor for block at %x ***\n", pBlock);
		}

		// keep the longest
		int t_len = pBlockdescriptor->m_pfilename != 0 ? strlen(pBlockdescriptor->m_pfilename) : 0;
		if(t_len > max_namelen) {
			max_namelen = t_len;
		}
	}

	// the printed number of the object
	int count = 1;

	// iterate over descriptors again and dump leaked objects ...
	for(aeBlockDescriptor_map::iterator x = m_blockdescriptormap.begin(); x != m_blockdescriptormap.end(); ++x) {
		// ok, here follows the output-stuff

		// data again
		void *pBlock = x->first;
		aeBlockDescriptor *pBlockdescriptor = x->second;
    
		// print out first line: "--- <nr> <addr> <size> <file> <line>"
		std::cout << "-- #";
		std::cout.width(3);
		std::cout << count << "  address:" << pBlock << "  size:";
		std::cout.width(6);

		// size: b,k,m
		int size = pBlockdescriptor->m_size;
		int format = 0;
		while(size >= 1000000) {
			size /= 1000;
			format++;
		}
		std::cout << size;
		switch(format) {
		case 0:
			std::cout << "b";
			break;
		case 1:
			std::cout << "k";
			break;
		case 2:
			std::cout << "m";
			break;
		}

		if(pBlockdescriptor->m_pfilename != NULL) {
			std::cout << "  filename:";
			std::cout.width(max_namelen);
			std::cout << pBlockdescriptor->m_pfilename << "  line:";
			std::cout.width(4);
			std::cout << pBlockdescriptor->m_linenumber << std::endl;
		}

		// reduce dump-len to max. constructor-passed size
		int len = (int)pBlockdescriptor->m_size < m_maxdumpbytes ? pBlockdescriptor->m_size : m_maxdumpbytes;;

		// rows..
		int rows = len / (m_blocks * 4);
		// "half" rows ..
		if(len % (m_blocks * 4) > 1)
			rows ++;

		// each row
		int offset = 0;
		for(int row = 0; row < rows; row++) {
			// beginning of line: <offset>
			std::cout.width(4);
			std::cout.unsetf(std::ios::dec | std::ios::oct);
			std::cout.setf(std::ios::hex);
			std::cout << offset << ": ";

			// as i need to draw each byte "2 times", i use
			// "offset" as a row-incremented offset, and let
			// "lineoffset" increment 2 times from 0 to "eol"
			int lineoffset;

			// hexdump: "blocks * columns a 4 bytes"
			lineoffset = 0;
			for(int block = 0; block < m_blocks; block++) {
				for(int i = 0;i < 4; i++) {
					std::cout.fill('0');
					if(lineoffset + offset < len) {
						std::cout << std::setw(2) << ((unsigned short)((const char*)pBlockdescriptor->m_addr)[offset + lineoffset++] & 0xff);
					} else {
						std::cout << "  ";
					}
					std::cout.fill(' ');
				}
				std::cout << " ";
			}
			// separator hex - ascii
			std::cout << "| ";
			// ascii: "blocks * columns a 4 bytes"
			lineoffset = 0;
			for(int block = 0; block < m_blocks; block++) {
				for(int i = 0; i < 4; i++) {
					// const char *val = (const char*)pBlockdescriptor->m_addr; 
					unsigned char tval;
					if(lineoffset + offset < len) {
						tval = (unsigned char)((const char*)pBlockdescriptor->m_addr)[offset + lineoffset++];
						if(tval < 0x21 || (tval > 0x7e && tval < 0xa1)) {
							tval = '.';
						}
					} else {
						tval=' ';
					}
					std::cout << tval;
				}
				std::cout << " ";
			}

			// finally increment "offset" the amount of actually written bytes
			// simply taking last value from lineoffset
			offset += lineoffset;

			// line end, reset some iostream-settings
			std::cout.unsetf(std::ios::hex | std::ios::oct);
			std::cout.setf(std::ios::dec);
			std::cout << std::endl;
		}
		count++;
	}

	if(m_blockdescriptormap.size() > 0) {
		Report(0, "*** object dump finished - %d objects leaked ***\n", m_blockdescriptormap.size());
	}
}

void aeMemoryManager::Registerblock(void *addr, size_t size, const char *filename, int linenumber)
{
	if(pglob_self == NULL) {
		return;
	}

	aeBlockDescriptor *desc = new aeBlockDescriptor(addr, size, filename, linenumber);
	pglob_self->m_blockdescriptormap.insert(std::make_pair(addr, desc));
}

void aeMemoryManager::Unregisterblock(void *addr)
{
	if(pglob_self == NULL) {
		return;
	}

	aeBlockDescriptor *pDesc = pglob_self->m_blockdescriptormap.find(addr)->second;

	if(pDesc != NULL) {
		pglob_self->m_blockdescriptormap.erase(addr);
		delete(pDesc);
	}
}
