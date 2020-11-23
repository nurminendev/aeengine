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

#ifndef __AELIB_AEGEOM_MODEL_H__
#define __AELIB_AEGEOM_MODEL_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aeengine/eflags.h>
#include <aegeom/object.h>
#include <aegfx/material.h>
#include <aemdlldr/mdlstruct.h>

/** 
 * A 3D model object.
 * 
 */
class aeModel: public aeObject {
 protected:
	unsigned int numFrames;
	unsigned int numVertices;
	unsigned int numTriangles;
	unsigned int numTexCoords;
	modelState_t modelState;
	bool isAnimating;

 public:
	virtual ~aeModel();

	/** 
	 * Draw this model. This is called by aeEngine::Render(). You shouldn't need to call
	 * this yourself.
	 *
	 */
	virtual void Draw(aeEngineflags *) = 0;

	/** 
	 * Animate the model.
	 * Animate the model given the start frame, end frame, and interpolation percentage.
	 * 
	 * @param int Frame to start the animation.
	 * @param int Frame to end the animation.
	 * @param float Interpolation percentage.
	 */
	virtual int Animate(aeEngineflags *) = 0;

	/** 
	 * Render a single frame of the model.
	 */
	virtual int RenderFrame(aeEngineflags *) = 0;

	/** 
	 * Set model animation given start frame, end frame, and interpolation percentage.
	 * 
	 * @param startframe Start frame for animation.
	 * @param endframe End frame for animation
	 * @param interpol Interpolation percentage.
	 */
	virtual void SetAnimation(int startframe, int endframe, float percent) = 0;

	/** 
	 * Set model frame to render. This will render a single still frame of a model.
	 * 
	 * @param keyframe Frame of model to render.
	 */
	virtual void SetFrame(int keyframe) = 0;

	/** 
	 * Get the model's state.
	 * 
	 * 
	 * @return The model's state.
	 */
	virtual modelState_t GetState() = 0;

	/** 
	 * Set the state for this model.
	 * 
	 * @param modelState_t The model's state.
	 */
	virtual void SetState(modelState_t) = 0;

	/** 
	 * Used to check if this model is currently animating.
	 * 
	 * 
	 * @return True if the model is animating, false if not.
	 */
	virtual bool IsAnimating();
};

#endif // __AELIB_AEGEOM_MODEL_H__
