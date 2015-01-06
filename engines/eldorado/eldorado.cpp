/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */
#include "common/archive.h"
#include "common/debug-channels.h"
#include "common/file.h"
#include "common/foreach.h"
#include "common/fs.h"
#include "common/config-manager.h"

#include "gui/error.h"
#include "gui/gui-manager.h"
#include "gui/message.h"

#include "engines/engine.h"
 
#include "eldorado/eldorado.h"
 
namespace ElDorado {
 
ElDoradoEngine::ElDoradoEngine(OSystem *syst) 
 : Engine(syst) {
	debug("ElDoradoEngine::ElDoradoEngine");
}
 
ElDoradoEngine::~ElDoradoEngine() {
	debug("ElDoradoEngine::~ElDoradoEngine");
}
 
Common::Error ElDoradoEngine::run() { 
	// Your main even loop should be (invoked from) here.
	debug("ElDoradoEngine::run: Hello, World!");

	return Common::kNoError;
}
 
} // End of namespace ElDorado
