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

#ifndef __AELIB_AESYS_TIMER_H__
#define __AELIB_AESYS_TIMER_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aereg/base.h>

/** 
 * This is a general virtual/system timer class.
 *
 */
class aeTimer: public aeBase {
	AECF_CNDEF

 private:
	float FPS;
	float FPScounter;
	float FrameInterval;
	float FrameTime;
	float LastFrameTime;
	float currentTime;

 public:
	aeTimer();
	~aeTimer();

	/** 
	 * Get the current FPS.
	 * 
	 * 
	 * @return Current FPS.
	 */
	float GetFPS() const { return FPS; }

	/** 
	 * Get the interval between two frames.
	 * This is used by aeCamera to create time based movement.
	 * 
	 * 
	 * @return The interval.
	 */
	float GetFrameInterval() const { return FrameInterval; }

	/** 
	 * Calculate the current frame rate.
	 * 
	 */
	void CalculateFrameRate();
};

#endif // __AELIB_AEENGINE_CTIMER_H__
