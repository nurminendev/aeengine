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
#include <aeutil/databuffer.h>
#include <aeutil/util.h>

aeDataBuffer::aeDataBuffer()
{
	AECF_CNAME("aeDataBuffer")
	databuf = NULL;
}

aeDataBuffer::aeDataBuffer(const char *dfile, bool binary)
{
	AECF_CNAME("aeDataBuffer")
	if(!Read(dfile, binary)) {
		Report(0, "Failed to read file %s\n", dfile);
	}
}
aeDataBuffer::~aeDataBuffer()
{
	if(databuf != NULL) {
		delete databuf;
	}
}

bool aeDataBuffer::Read(const char *dfile, bool binary)
{
	FILE *datafile = NULL;
	if(binary) {
		datafile = fopen(dfile, "rb");
	} else {
		datafile = fopen(dfile, "r");
	}

	if(datafile == NULL) {
		Report(0, "Can't open file %s\n", dfile);
		return false;
	}

	// Obtain file size
	fseek(datafile, 0, SEEK_END);
	size = ftell(datafile);
	rewind(datafile);

	databuf = new char[size];

	fread(databuf, 1, size, datafile);

	int fread_err = ferror(datafile);

	if(fread_err) {
		aeUtil::Report("ae.databuffer.Read", "Can't read file %s\n", dfile);
		return false;
	}

	fclose(datafile);

	return true;
}
