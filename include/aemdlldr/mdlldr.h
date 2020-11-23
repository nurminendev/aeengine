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

#ifndef __AEPLUGIN_AEMODELLOADER_MDLLDR_H__
#define __AEPLUGIN_AEMODELLOADER_MDLLDR_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aegfx/material.h>
#include <aemdlldr/md2object.h>
#include <aemdlldr/mdlstruct.h>
#include <aereg/registry.h>

/** @defgroup mdltypes AE model type enumerations
 * AE Model type definitions.
 * @{
 */

/// AE model type enumerations.
enum aeModelType {
	/// A Quake2 MD2 model
	AE_MODEL_MD2,
	/// An unknown model type
	AE_MODEL_UNKNOWN
};

/** @} */

/** 
 * Interface to the model loader plugin.
 */
class aeModelLoader: public aePlugin {
	AECF_CNDEF

 private:
	aeRegistry *aereg;

	aeModelType GetModelType(char *);
	// load model only
	aeMD2Object *LoadMD2(char *mdlstr, char *modelFile);
	// load model and material (skin) at the same time
	aeMD2Object *LoadMD2(char *mdlstr, char *modelFile, aeMaterial *mat);

 public:
	aeModelLoader(aeRegistry *aeReg);
	~aeModelLoader();

	/** 
	 * Load a model given a name, model file, and a material.
	 * 
	 * @param mdlname The name of the model.
	 * @param mdlfile The model file.
	 * @param mat The model's material
	 * 
	 * @return An aeModel instance ready to be used.
	 */
	virtual aeModel *LoadModel(char *mdlname, char *mdlfile, aeMaterial *mat);
};

#endif // __AEPLUGIN_AEMODELLOADER_MDLLDR_H__
