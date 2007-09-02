/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id$
 *
 */

/**
 * @file PluginMgr.h
 * Declares PluginMgr, loader for GemRB plugins
 * @author The GemRB Project
 */

#ifndef PLUGINMGR_H
#define PLUGINMGR_H

#include "../../includes/win32def.h"
#include "../../includes/globals.h"
#include <vector>

#ifdef WIN32

#ifdef GEM_BUILD_DLL
#define GEM_EXPORT __declspec(dllexport)
#else
#define GEM_EXPORT __declspec(dllimport)
#endif

#else
#define GEM_EXPORT
#endif

#ifdef WIN32
typedef HINSTANCE LibHandle;
#else
typedef void *LibHandle;
#endif

/**
 * @class PluginMgr
 * Class for loading GemRB plugins from shared libraries or DLLs.
 * It goes over all appropriately named files in PluginPath directory
 * and tries to load them one after another.
 */

typedef struct InterfaceElement {
	void *mgr;
	bool free;
} InterfaceElement;

class GEM_EXPORT PluginMgr {
public:
	PluginMgr(char* pluginpath);
	~PluginMgr(void);
private:
	std::vector< ClassDesc*> plugins;
	std::vector< LibHandle> libs;
public:
	bool IsAvailable(SClass_ID plugintype) const;
	void* GetPlugin(SClass_ID plugintype) const;
	std::vector<InterfaceElement> *GetAllPlugin(SClass_ID plugintype) const;	
	void FreePlugin(void* ptr);
	size_t GetPluginCount() const { return plugins.size(); }
};

#endif
