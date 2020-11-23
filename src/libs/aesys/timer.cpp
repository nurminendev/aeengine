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

#include <aedefs.h>
#include <aesys/timer.h>

aeTimer::aeTimer()
{
	AECF_CNAME("aeTimer")
	FPS = 0.0;
	FPScounter = 0.0;
	FrameTime = 0.0;
	LastFrameTime = 0.0;
	currentTime = 0.0;
	FrameInterval = 0.0;
}

aeTimer::~aeTimer()
{
}

void aeTimer::CalculateFrameRate()
{
	currentTime = (float)SDL_GetTicks() * 0.001f;

	FrameInterval = currentTime - FrameTime;
	FrameTime = currentTime;

	// Increase the frame counter
	++FPScounter;

	// Now we want to subtract the current time by the last time that was stored
	// to see if the time elapsed has been over a second, which means we found our FPS.
	if(currentTime - LastFrameTime > 1.0) {
		// Here we set the lastTime to the currentTime
		LastFrameTime = currentTime;

		FPS = FPScounter;

		// reset the frame counter
		FPScounter = 0;
	}
}
