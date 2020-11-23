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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif
#include <aedefs.h>
#include <aeengine/camera.h>
#include <aeengine/engine.h>
#include <aegeom/object.h>
#include <aegfx/material.h>
#include <aegfx/texture.h>
#include <aeplugin/plugin.h>
#include <aereg/registry.h>
#include <aesys/system.h>
#include <aeutil/util.h>

aeRegistry *aeRegistry::self_ptr = 0;

aeRegistry::aeRegistry(int argc, char *argv[])
{
	AECF_CNAME("aeRegistry")

	int vidflags = 0;
	char *ptr;
	int width = 640, height = 480;

	self_ptr = this;

	objectpool.resize(0);
	if(DEBUG) {
		ASSERT(objectpool.size() == 0, "objectpool.size() == 0");
	}
	materialpool.resize(0);
	if(DEBUG) {
		ASSERT(materialpool.size() == 0, "materialpool.size() == 0");
	}
	texturepool.resize(0);
	if(DEBUG) {
		ASSERT(texturepool.size() == 0, "texturepool.size() == 0");
	}

	if(argc > 1) {
		for(int n = 1; n < argc; n++) {
			if((ptr = strstr(argv[n], "-help")) != NULL) {
				cmdlinehelp = true;
			} else if((ptr = strstr(argv[n], "-mode=")) != NULL) {
				sscanf(ptr + 6, "%dx%d", &width, &height);
			} else if((ptr = strstr(argv[n], "-fullscreen")) != NULL) {
				vidflags |= SDL_FULLSCREEN;
			}
		}
	}

	timer = new aeTimer();
	system = new aeSystem(this);
	engine = new aeEngine(this, width, height, vidflags);
}

aeRegistry::~aeRegistry()
{
	unsigned int i;

	if(system)
		delete system;
	if(engine)
		delete engine;
	if(timer)
		delete timer;

	for(i = 0; i < objectpool.size(); i++) {
		delete objectpool[i];
	}
	objectpool.clear();

	for(i = 0; i < materialpool.size(); i++)
		delete materialpool[i];
	materialpool.clear();

	for(i = 0; i < texturepool.size(); i++)
		delete texturepool[i];
	texturepool.clear();

	for(i = 0; i < pluginpool.size(); i++)
		delete pluginpool[i];
	pluginpool.clear();
}

void aeRegistry::Help()
{
	fprintf(stdout, "Available commandline options are:\n");
	fprintf(stdout, "\t-mode=WxH\t\tStart into display mode W x H\n");
	fprintf(stdout, "\t-fullscreen\t\tStart in fullscreen mode\n");
	fprintf(stdout, "\n");
}

aeObject *aeRegistry::FindObject(unsigned int objnum)
{
	return objectpool[objnum];
}

aeObject *aeRegistry::FindObjectByName(const char *objname)
{
	for(unsigned int i = 0; i < GetObjectCount(); i++) {
		aeObject *obj = FindObject(i);
		if(obj != NULL) {
			if(strstr(obj->GetName(), objname)) {
				return obj;
			}
		}
	}
	return NULL;
}

aeMaterial *aeRegistry::FindMaterial(unsigned int matnum)
{
	return materialpool[matnum];
}


aeMaterial *aeRegistry::FindMaterialByName(const char *matname)
{
	for(unsigned int i = 0; i < GetMaterialCount(); i++) {
		aeMaterial *mat = FindMaterial(i);
		if(mat != NULL) {
			if(strstr(mat->GetName(), matname)) {
				return mat;
			}
		}
	}
	return NULL;
}

aeTexture *aeRegistry::FindTexture(unsigned int texnum)
{
	return texturepool[texnum];
}


aeTexture *aeRegistry::FindTextureByName(const char *texname)
{
	for(unsigned int i = 0; i < GetTextureCount(); i++) {
		aeTexture *tex = FindTexture(i);
		if(tex != NULL) {
			if(strstr(tex->GetName(), texname)) {
				return tex;
			}
		}
	}
	return NULL;
}

void aeRegistry::PushObjectToPool(aeObject *obj)
{
	objectpool.push_back(obj);
}

void aeRegistry::PushMaterialToPool(aeMaterial *mat)
{
	materialpool.push_back(mat);
}

void aeRegistry::PushTextureToPool(aeTexture *tex)
{
	texturepool.push_back(tex);
}

aePlugin *aeRegistry::LoadPlugin(aePluginID id)
{
	aePlugin *plugin = NULL; // Pointer to plugin instance

	// Check if we're on dlopen() or LoadLibrary() system (unix or win32)
#ifndef WIN32
	void *plugin_handle; // Plugin dlopen() handle
	const char *error;
#else
	HINSTANCE plugin_handle; // Plugin LoadLibrary() handle
#endif
	PLG_ENTRY PLUGIN_ENTRY = NULL; // Pointer to plugin entry symbol
	char *ae_env; // AEROOT env variable
	char *plugindll; // Full path to plugin dll
	char *pluginstring = ""; // Plugin name (e.g. "aeTerrMan")

	// Check which plugin to load
	if(id == AE_PLUGIN_aeModelLoader)
		pluginstring = "mdlldr";
	if(id == AE_PLUGIN_aeTerrMan)
		pluginstring = "terrman";
	if(id == AE_PLUGIN_aeTextureLoader)
		pluginstring = "txtldr";

	if((ae_env = getenv("AEROOT")) == NULL) {
		ae_env = "./";
	}

	// Allocate memory for the AEROOT env variable (path) and the plugin (file) + its extension
	// + NUL-byte
	plugindll = new char[strlen(ae_env) + strlen(pluginstring) + 4];
	sprintf(plugindll, "%s/%s.so", ae_env, pluginstring);

#ifndef WIN32
	plugin_handle = dlopen(plugindll, RTLD_LAZY);
	if(!plugin_handle) {
		Report(0, "Couldn't load the %s plugin: %s\n", pluginstring, dlerror());
		delete plugindll;
		return NULL;
	}
	PLUGIN_ENTRY = (PLG_ENTRY)dlsym(plugin_handle, "PLUGIN_ENTRY");
	error = dlerror();
	if(error) {
		Report(0, "Unable find the GET_PLUGIN_PTR symbol for %s: %s\n", pluginstring, error);
		delete plugindll;
		return NULL;
	}
	plugin = (*PLUGIN_ENTRY)(this);
#else
	plugin_handle = LoadLibrary(plugindll);
	if(!plugin_handle) {
		Report(0, "Couldn't load the %s plugin.\n", pluginstring);
		delete plugindll;
		return NULL;
	}
	PLUGIN_ENTRY = (PLG_ENTRY)GetProcAddress(plugin_handle, "PLUGIN_ENTRY");
	plugin = (*PLUGIN_ENTRY)(this);
#endif

	delete plugindll;

	if(plugin != NULL)
		pluginpool.push_back(plugin);

	return plugin;
}
