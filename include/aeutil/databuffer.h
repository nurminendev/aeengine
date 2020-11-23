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

#ifndef __AELIB_AEUTIL_DATABUFFER_H__
#define __AELIB_AEUTIL_DATABUFFER_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aereg/base.h>

/** 
 * A generic data buffer class.
 * 
 */
class aeDataBuffer: public aeBase {
	AECF_CNDEF

 private:
	char *databuf;
	size_t size;

 public:
	aeDataBuffer();
	aeDataBuffer(const char *dfile, bool binary = false);
	~aeDataBuffer();

	/** 
	 * Read a file into the buffer.
	 * 
	 * @param dfile Path to the file.
	 * @param binary Binary mode.
	 * 
	 * @return true if the file was read succesfully.
	 */
	bool Read(const char *dfile, bool binary = false);

	/** 
	 * Get the data from the buffer.
	 * 
	 * 
	 * @return The data.
	 */
	char *GetData() const { return databuf; }

	/** 
	 * Get the size of the data in the buffer.
	 * 
	 * 
	 * @return The data size.k
	 */
	size_t GetSize() const { return size; }
};

#endif // __AELIB_AEUTIL_DATABUFFER_H__
