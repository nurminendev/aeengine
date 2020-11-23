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
#include <aeengine/camera.h>
#include <aeengine/engine.h>
#include <aegeom/vector3.h>
#include <aereg/registry.h>
#include <aesys/timer.h>

aeCamera::aeCamera()
{
	AECF_CNAME("aeCamera")
	engine = aeRegistry::self_ptr->GetEngine();
	timer = aeRegistry::self_ptr->GetTimer();
	cam_pos = aeVector3(0.0, 0.0, 0.0);
	cam_view = aeVector3(0.0, 1.0, 0.5);
	cam_upvector = aeVector3(0.0, 1.0, 0.0);
	cam_speed = 100.0;
	upPressed = downPressed = rightPressed = leftPressed = false;
}

aeCamera::~aeCamera()
{
}

void aeCamera::PositionCamera(float pos_x, float pos_y, float pos_z,
							  float view_x, float view_y, float view_z,
							  float upvec_x, float upvec_y, float upvec_z)
{
	cam_pos = aeVector3(pos_x, pos_y, pos_x);
	cam_view = aeVector3(view_x, view_y, view_z);
	cam_upvector = aeVector3(upvec_x, upvec_y, upvec_z);
}

void aeCamera::PositionCamera(aeVector3 posVec, aeVector3 viewVec, aeVector3 upVec)
{
	cam_pos = posVec;
	cam_view = viewVec;
	cam_upvector = upVec;
}

void aeCamera::SetViewByMouse()
{
	int mouse_x, mouse_y;
	float angle_y = 0.0f;
	float angle_z = 0.0f;
	int middle_x = engine->GetScreenWidth() / 2;
	int middle_y = engine->GetScreenHeight() / 2;
	static float current_rot_x = 0.0f;

	SDL_GetMouseState(&mouse_x, &mouse_y);

	if((mouse_x == middle_x) && (mouse_y == middle_y)) {
		return;
	}

	SDL_WarpMouse(middle_x, middle_y);

	angle_y = (float)((middle_x - mouse_x)) / 1000.0f;
	angle_z = (float)((middle_y - mouse_y)) / 1000.0f;

	// Restrict the camera from doing a full 360 loop
	current_rot_x -= angle_z;

	// If the current rotation (in radians) is greater than 1.0, we want to cap it.
	if(current_rot_x > 1.0f) {
		current_rot_x = 1.0f;
	} else if(current_rot_x < -1.0f) {
		// Check if the rotation is below -1.0, if so we want to make sure it doesn't continue
		current_rot_x = -1.0f;
	} else {
		// Otherwise, we can rotate the view around our position
		// To find the axis we need to rotate around for up and down
		// movements, we need to get a perpendicular vector from the
		// camera's view vector and up vector.  This will be the axis.
		aeVector3 tempVec = cam_view - cam_pos;
		aeVector3 vAxis = tempVec % cam_upvector;
		vAxis = vAxis.Normalize();

		// Rotate around our perpendicular axis and along the y-axis
		RotateView(-angle_z, vAxis.x, vAxis.y, vAxis.z);
		RotateView(angle_y, 0, 1, 0);
	}
}

void aeCamera::RotateView(float angle, float x, float y, float z)
{
	aeVector3 vNewView;

	// Get the view vector (The direction we are facing)
	aeVector3 vView = cam_view - cam_pos;

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point
	vNewView.x = (cosTheta + (1 - cosTheta) * x * x) * vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta) * vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta) * vView.z;

	// Find the new y position for the new rotated point
	vNewView.y = ((1 - cosTheta) * x * y + z * sinTheta) * vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y) * vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta) * vView.z;

	// Find the new z position for the new rotated point
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta) * vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta) * vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z) * vView.z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated view of our camera.
	cam_view = cam_pos + vNewView;
}

void aeCamera::StrafeCamera(float speed)
{   
	// Add the strafe vector to our position
	cam_pos.x += cam_strafe.x * speed;
	cam_pos.z += cam_strafe.z * speed;

	// Add the strafe vector to our view
	cam_view.x += cam_strafe.x * speed;
	cam_view.z += cam_strafe.z * speed;
}

void aeCamera::MoveCamera(float speed)
{
	// Get the current view vector (the direction we are looking)
	aeVector3 vVector = cam_view - cam_pos;
	vVector = vVector.Normalize();

	cam_pos.x += vVector.x * speed;
	cam_pos.y += vVector.y * speed;
	cam_pos.z += vVector.z * speed;
	cam_view.x += vVector.x * speed;
	cam_view.y += vVector.y * speed;
	cam_view.z += vVector.z * speed;
}

void aeCamera::CheckForMovement()
{
	float speed = cam_speed * timer->GetFrameInterval();

	// Check if we hit the Up arrow or the 'w' key
	if(upPressed) {
		// Move our camera forward by a positive SPEED
		MoveCamera(speed);
	}

	// Check if we hit the Down arrow or the 's' key
	if(downPressed) {
		// Move our camera backward by a negative SPEED
		MoveCamera(-speed);
	}

	// Check if we hit the Left arrow or the 'a' key
	if(leftPressed) {
		// Strafe the camera left
		StrafeCamera(-speed);
	}

	// Check if we hit the Right arrow or the 'd' key
	if(rightPressed) {
		// Strafe the camera right
		StrafeCamera(speed);
	}
}

void aeCamera::Update() 
{
	// Initialize a variable for the cross product result
	aeVector3 tempvec = cam_view - cam_pos;
	aeVector3 vCross = tempvec % cam_upvector;

	// Normalize the strafe vector
	cam_strafe = vCross.Normalize();

	// Move the camera's view by the mouse
	SetViewByMouse();

	// This checks to see if the keyboard was pressed
	CheckForMovement();

	// We calculate our frame rate and set our frame interval for time based movement
	timer->CalculateFrameRate();
}

void aeCamera::Look()
{
	// Give openGL our camera position, then camera view, then camera up vector
	gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z,
			  cam_view.x, cam_view.y, cam_view.z,
			  cam_upvector.x, cam_upvector.y, cam_upvector.z);
}
