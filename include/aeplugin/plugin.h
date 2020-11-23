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

#ifndef __AELIB_AEPLUGIN_PLUGIN_H__
#define __AELIB_AEPLUGIN_PLUGIN_H__

#define ONLY_INCLUDE_STD
#include <aedefs.h>
#undef ONLY_INCLUDE_STD
#include <aereg/base.h>

/** @defgroup pluginIDs AE Plugin ID definitions.
 * AE plugin ID definitions.
 * @{
 */
enum aePluginID {
	AE_PLUGIN_aeModelLoader,
	AE_PLUGIN_aeTerrMan,
	AE_PLUGIN_aeTextureLoader
};

/** @} */

/** 
 * A base class for all plugins.
 */
class aePlugin: public aeBase {
 public:
	virtual ~aePlugin() {}

	/// Plugin ID
	aePluginID myID;

	/** 
	 * Retrieve the plugin ID.
	 * 
	 * 
	 * @return The plugin ID.
	 * @sa aePluginID
	 */
    aePluginID GetPluginID() const { return myID; }
};

#endif // __AELIB_AEPLUGIN_PLUGIN_H__
