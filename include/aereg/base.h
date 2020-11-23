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

#ifndef __AELIB_AEREG_BASE_H__
#define __AELIB_AEREG_BASE_H__

/** 
 * This is a base class for all objects.
 */
class aeBase {
 private:
	void log(int loglevel, const char *logstr);

 protected:
	int LOGLEVEL;

	/** 
	 * General in-engine report function with loglevel.
	 * 
	 * @param loglevel Loglevel.
	 * @param msg Message (with possible format characters, think of printf).
	 * @param  ... Possible format variables (think of printf).
	 */
	virtual void Report(int loglevel, const char *msg, ...);

	/** 
	 * General in-engine assert function.
	 * 
	 * @param isok Expression to test.
	 * @param desc Description to print out if the expression fails (can include printf style formatting).
	 * @param  ... Format variables (think of printf).
	 */
	virtual void ASSERT(bool isok, char *desc, ...);

 public:
	virtual ~aeBase();
};

#endif // __AELIB_AEREG_BASE_H__
