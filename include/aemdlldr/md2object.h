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

#ifndef __AELIB_AEGEOM_MD2OBJECT_H__
#define __AELIB_AEGEOM_MD2OBJECT_H__

#include <aedefs.h>
#include <aeengine/eflags.h>
#include <aegeom/object.h>
#include <aegeom/model.h>
#include <aegeom/vector3.h>
#include <aegfx/material.h>
#include <aegfx/texcoord2.h>
#include <aegfx/texture.h>
#include <aemdlldr/mdlstruct.h>

/** 
 * This class represents a single MD2 model.
 * Normally you don't deal with this class directly, but with the aeModel class.
 *
 * @sa aeModel
 */
class aeMD2Object: public aeModel {
	AECF_CNDEF

 private:
	int frameSize;
	int currentFrame;
	int nextFrame;
	int startFrame;
	int endFrame;
	int keyFrame;
	float interpol;
	float percent;
	mesh_t *triIndex;

 public:
	aeMD2Object(char *mdlstr, aeVector3_vector *vertList, aeTexCoord2_vector *stList,
				mesh_t *triIdx, unsigned int numframes, unsigned int numverts, unsigned int numtris,
				unsigned int numst, unsigned int framesize);

	~aeMD2Object();

	/** 
	 * Draw the model. This is called by aeEngine::Render(). You shouldn't need to call this
	 * yourself.
	 * 
	 */
	void Draw(aeEngineflags *);

	/** 
	 * Animate the model given a start frame, end frame, and interpolation percentage.
	 * 
	 * @param startFrame Starting frame.
	 * @param endFrame Ending frame.
	 * @param percent Interpolation percentage.
	 */
	int Animate(aeEngineflags *);

	/** 
	 * Render a single frame of the model.
	 * 
	 * @param keyFrame The frame number.
	 */
	int RenderFrame(aeEngineflags *);

	/** 
	 * Set model animation given start frame, end frame, and interpolation percentage.
	 * 
	 * @param startframe Start frame for animation.
	 * @param endframe End frame for animation
	 * @param interpol Interpolation percentage.
	 */
	void SetAnimation(int startframe, int endframe, float percent);

	/** 
	 * Set model frame to render. This will render a single still frame of a model.
	 * 
	 * @param keyframe Frame of model to render.
	 */
	void SetFrame(int keyframe);

	/** 
	 * Retrieve animation state for the model.
	 * 
	 * 
	 * @return The animation state.
	 */
	modelState_t GetState();

	/** 
	 * Set the animation state for the model.
	 * 
	 * @param state Animation state.
	 */
	void SetState(modelState_t state);	
};

#endif // __AELIB_AEGEOM_MD2OBJECT_H__
