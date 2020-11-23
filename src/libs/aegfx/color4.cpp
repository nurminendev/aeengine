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
#include <aegfx/color4.h>

aeColor4::aeColor4()
{
	AECF_CNAME("aeColor4")
	red = 0.0;
	green = 0.0;
	blue = 0.0;
	alpha = 1.0;
}

aeColor4::aeColor4(float r, float g, float b, float a)
{
	AECF_CNAME("aeColor4")
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

aeColor4::~aeColor4()
{
}

void aeColor4::Set(float r, float g, float b, float a)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

void aeColor4::Clamp(float r, float g, float b, float a)
{
	if(red > r) red = r;
	if(green > g) green = g;
	if(blue > b) blue = b;
	if(alpha > a) alpha = a;
}

void aeColor4::ClampDown()
{
	if(red < 0) red = 0;
	if(green < 0) green = 0;
	if(blue < 0) blue = 0;
	if(alpha < 0) alpha = 0;
}

void aeColor4::Add(float r, float g, float b, float a) {
	red += r;
	green += g;
	blue += b;
	alpha += a;
}

void aeColor4::Subtract(float r, float g, float b, float a) {
	red -= r;
	green -= g;
	blue -= b;
	alpha -= a;
}
