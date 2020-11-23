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
#include <aereg/base.h>

#ifdef WIN32
#define vsnprintf _vsnprintf
#endif

aeBase::~aeBase()
{
}

void aeBase::log(int loglevel, const char *logstr)
{
	if(loglevel == 0 || loglevel <= LOGLEVEL) {
		std::clog << typeid(*this).name() << "@" << this << "> " << logstr;
	}
}

void aeBase::Report(int loglevel, const char *msg, ...)
{
	va_list vargs;
	char outBuff[256];

	if(strlen(msg) > 254) {
		std::clog << "aeBase::Report warn: logstring exceeded 254 bytes: " << msg << std::endl;
	}

	va_start(vargs, msg);
	vsnprintf(outBuff, sizeof(outBuff), msg, vargs);
	va_end(vargs);

	if(loglevel == 0 || loglevel <= LOGLEVEL) {
		log(loglevel, outBuff);
	}
}

void aeBase::ASSERT(bool isok, char *desc, ...)
{
	if(isok) {
		return;
	} else {
		char buf[256];
		char outBuf[256];

		va_list arg;

		va_start(arg, desc);
		vsnprintf(buf, sizeof(buf), desc, arg);
		va_end(arg);

		sprintf(outBuf, "ASSERT failed: %s\n", buf);
		log(0, outBuf);
		//exit(1);
	}
}
