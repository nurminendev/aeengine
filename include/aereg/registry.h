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

#ifndef __AELIB_AEREG_REGISTRY_H__
#define __AELIB_AEREG_REGISTRY_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aeengine/engine.h>
#include <aegeom/object.h>
#include <aegfx/material.h>
#include <aegfx/texture.h>
#include <aeplugin/plugin.h>
#include <aereg/base.h>
#include <aesys/system.h>
#include <aesys/timer.h>

/// Plugin fetching macro.
#define AE_GET_PLUGIN(Registry, Plugin) (Plugin *)Registry->LoadPlugin(AE_PLUGIN_##Plugin)

/// Typedef for pointer to plugin entry function
typedef aePlugin *(*PLG_ENTRY)(aeRegistry *aeReg);

class aeSystem;

/** 
 * This class is an interface to the global object registry.
 */
class aeRegistry: public aeBase {
	AECF_CNDEF

 private:
	aeTimer *timer;
	aeSystem *system;
	aeEngine *engine;
	std::vector<aeObject*> objectpool;
	std::vector<aeMaterial*> materialpool;
	std::vector<aeTexture*> texturepool;
	std::vector<aePlugin*> pluginpool;
	bool cmdlinehelp;

 public:
	/** 
	 * Initialize the registry.
	 * 
	 * @param argc argc from main().
	 * @param argv argv from main().
	 */
	aeRegistry(int argc, char *argv[]);
	~aeRegistry();

	/// Global registry self ref
	static aeRegistry *self_ptr;

	/** 
	 * Check if the -help flag was specified in the command line.
	 * 
	 * 
	 * @return true if -help was requested.
	 */
	bool CmdLineHelp() const { return cmdlinehelp; }

	/** 
	 * Print help.
	 * 
	 */
	void Help();

	/** 
	 * Get the timer pointer.
	 * 
	 * 
	 * @return A pointer to aeTimer.
	 */
	aeTimer *GetTimer() const { return timer; }

	/** 
	 * Get the engine pointer.
	 * 
	 * 
	 * @return A pointer to aeEngine-
	 */
	aeEngine *GetEngine() const { return engine; }

	/** 
	 * Get the system pointer.
	 * 
	 * 
	 * @return A pointer to aeSystem.
	 */
	aeSystem *GetSystem() const { return system; }

	/** 
	 * Find object by ID.
	 * 
	 * @param int The object ID.
	 * 
	 * @return The object.
	 */
	aeObject *FindObject(unsigned int);

	/** 
	 * Find object by name.
	 * 
	 * @param char * The object name.
	 * 
	 * @return The object.
	 */
	aeObject *FindObjectByName(const char *);

	/** 
	 * Get the number of objects in the objectpool.
	 * 
	 * 
	 * @return The number of objects.
	 */
	unsigned int GetObjectCount() const { return objectpool.size(); }

	/** 
	 * Find texture by ID.
	 * 
	 * @param int The texture ID.
	 * 
	 * @return The texture.
	 */
	aeTexture *FindTexture(unsigned int);

	/** 
	 * Find texture by name.
	 * 
	 * @param char * The texture name.
	 * 
	 * @return The texture.
	 */
	aeTexture *FindTextureByName(const char *);

	/** 
	 * Get the number of textures in the texturepool.
	 * 
	 * 
	 * @return The number of textures.
	 */
	unsigned int GetTextureCount() const { return texturepool.size(); }

	/** 
	 * Find material by ID.
	 * 
	 * @param int The material ID.
	 * 
	 * @return The material.
	 */
	aeMaterial *FindMaterial(unsigned int);

	/** 
	 * Find material by name.
	 * 
	 * @param char * The material name.
	 * 
	 * @return The material.
	 */
	aeMaterial *FindMaterialByName(const char *);

	/** 
	 * Get the number of materials in the materialpool.
	 * 
	 * 
	 * @return The number of materials.
	 */
	unsigned int GetMaterialCount() const { return materialpool.size(); }

	/** 
	 * Push an object to the objectpool.
	 * Use aeEngine::AddObject() to add an object.
	 * 
	 * @param aeObject * The object.
	 */
	void PushObjectToPool(aeObject *);

	/** 
	 * Push a texture to the texturepool.
	 * Normally you don't need to do this since the texture loader plugin will take care of it.
	 * 
	 * @param aeTexture * The texture.
	 */
	void PushTextureToPool(aeTexture *);

	/** 
	 * Push a material to the materialpool.
	 * Normally you don't need to do this since adding a material will do it automagically.
	 * 
	 * @param aeMaterial * The material.
	 */
	void PushMaterialToPool(aeMaterial *);

	/** 
	 * Load a plugin.
	 * Use the AE_GET_PLUGIN() macro to load a plugin.
	 * 
	 * @param aePluginID The plugin ID.
	 * 
	 * @return Pointer to the plugin.
	 */
	aePlugin *LoadPlugin(aePluginID);
};

#endif // __AELIB_AEREG_REGISTRY_H__
