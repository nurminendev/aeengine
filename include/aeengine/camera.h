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

#ifndef __AELIB_AEENGINE_CAMERA_H__
#define __AELIB_AEENGINE_CAMERA_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aeengine/engine.h>
#include <aegeom/vector3.h>
#include <aereg/base.h>
#include <aesys/timer.h>

class aeEngine;

/**
 * This is a single camera object that can be attached to the engine.
 * Use engine->AttachCamera() to attach the camera.
 *
 * @sa aeEngine::AttachCamera()
 */
class aeCamera: public aeBase {
	AECF_CNDEF

 private:
	aeEngine *engine;
	aeTimer *timer;

	aeVector3 cam_pos; // camera's position
	aeVector3 cam_view; // camera's view
	aeVector3 cam_upvector; // camera's up vector
	aeVector3 cam_strafe; // camera's strafe vector
	float cam_speed; // camera's speed

	void RotateView(float angle, float x, float y, float z);

	// This moves the camera's view by the mouse movements (First person view)
	void SetViewByMouse();
	// This rotates the camera around a point (I.E. your character).
	void RotateAroundPoint(aeVector3 vCenter, float x, float y, float z);
	// This strafes the camera left or right depending on the speed (+/-) 
	void StrafeCamera(float speed);
	// This will move the camera forward or backward depending on the speed
	void MoveCamera(float speed);
	// This checks for keyboard movement
	void CheckForMovement();

 public:
	aeCamera();
	~aeCamera();

	bool upPressed, downPressed, rightPressed, leftPressed;

	/**
	 * Get the position vector of the camera.
	 * 
	 * 
	 * @return Camera The camera's position.
	 */
	aeVector3 GetPosition() const { return cam_pos; }

	/** 
	 * Get the view vector of the camera.
	 * 
	 * 
	 * @return The camera's view vector.
	 */
	aeVector3 GetView() const { return cam_view; }

	/** 
	 * Get the up vector of the camera.
	 * 
	 * 
	 * @return The camera's up vector.
	 */
	aeVector3 GetUpVector() const { return cam_upvector; }

	/** 
	 * Get the strafe vector of the camera.
	 * 
	 * 
	 * @return The camera's strafe vector.
	 */
	aeVector3 GetStrafe() const { return cam_strafe; }

	/** 
	 * Set the camera position.
	 * This (re)places the camera based on position, view (where it is looking at), and the
	 * 'up' vector.
	 * 
	 * @param pos_x Camera x position.
	 * @param pos_y Camera y position.
	 * @param pos_z Camera z position.
	 * @param view_x Camera view x.
	 * @param view_y Camera view y.
	 * @param view_z Camera view z.
	 * @param upvec_x Camera up vector x.
	 * @param upvec_y Camera up vector y.
	 * @param upvec_z Camera up vector z.
	 */
	void PositionCamera(float pos_x, float pos_y, float pos_z,
						float view_x, float view_y, float view_z,
						float upvec_x, float upvec_y, float upvec_z);

	/** 
	 * Set the camera position.
	 * This (re)places the camera based on position vector,
	 * view vector, and the 'up' vector.
	 * 
	 * @param posVec Position vector.
	 * @param viewVec View vector.
	 * @param upVec Up vector.
	 */
	void PositionCamera(aeVector3 posVec, aeVector3 viewVec, aeVector3 upVec);

	/** 
	 * Update the camera.
	 * This should be called each frame.
	 * 
	 */
	void Update();

	/** 
	 * Get FPS.
	 * 
	 * 
	 * @return Current FPS.
	 */
	float GetFPS() const { return timer->GetFPS(); }

	// This uses gluLookAt() to tell OpenGL where to look
	void Look();
};

#endif // __AELIB_AEENGINE_CAMERA_H__
