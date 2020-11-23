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
#include <aeutil/util.h>

#ifdef WIN32
#define vsnprintf _vsnprintf
#endif

void aeUtil::Report(const char *from, const char *desc, ...)
{
	va_list arg;
	char buf[256];

	va_start(arg, desc);
	vsnprintf(buf, sizeof(buf), desc, arg);
	va_end(arg);

	if(from != NULL)
		std::clog << from << ": " << buf;
	else
		std::clog << buf;

	return;
}

bool aeUtil::InStr(char *searchstr, char *str)
{
	char *endofstr;
	unsigned int idx = 0;

	endofstr = str + strlen(str);

	while(str < endofstr) {
		idx = strcspn(str, " ");

		if((strlen(searchstr) == idx) && (strncmp(searchstr, str, idx) == 0)) {
			return true;
		}

		str += (idx + 1);
	}
	return false;
}

aeVector3 aeUtil::CalculateNormal(const aeVector3 &v1, const aeVector3 &v2, const aeVector3 &v3)
{
	aeVector3 a, b, result;
	float length;

	a = v1 - v2;
	b = v1 - v3;

	result.x = (a.y * b.z) - (b.y * a.z);
	result.y = (b.x * a.z) - (a.x * b.z);
	result.z = (a.x * b.y) - (b.x * a.y);

	length = result.Magnitude();

	return aeVector3(result.x / length, result.y / length, result.z / length);
}
