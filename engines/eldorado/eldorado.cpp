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
#include "common/events.h"
#include "common/system.h"


#include "gui/error.h"
#include "gui/message.h"

#include "engines/util.h"
#include "engines/engine.h"
 
#include "eldorado/eldorado.h"

#include "video/bink_decoder.h"
 
namespace ElDorado {
 
ElDoradoEngine::ElDoradoEngine(OSystem *syst) 
 : Engine(syst) {

 	_system = syst;
	_video = new Video::BinkDecoder();

	debug("ElDoradoEngine::ElDoradoEngine");

	debug("Path is: %s", ConfMan.get("path").c_str());
}
 
ElDoradoEngine::~ElDoradoEngine() {
	debug("ElDoradoEngine::~ElDoradoEngine");

}
 
Common::Error ElDoradoEngine::run() { 
	// Your main even loop should be (invoked from) here.
	debug("ElDoradoEngine::run: Hello, World!");

	initGraphics(640, 480, true, NULL);

	// Play logos
	playVideo("gmovies/dwlogo.bik");
	playVideo("gmovies/revlogo.bik");
	playVideo("gmovies/ubilogo.bik");
	playVideo("gmovies/lsplogo.bik");

	playVideo("gmovies/intro.bik");
	playVideo("gmovies/introend.bik");

	// Main Loop
	// do {
	// 	pollKeyboard();

	// 	_system->updateScreen();
	// 	_system->delayMillis(60);
	// } while (!shouldQuit());

	return Common::kNoError;
}


void ElDoradoEngine::playVideo(const Common::String &filename) {
	if (!_video->loadFile(filename)) {
		warning("Could not play %s", filename.c_str());
		return;
	}

	debug("Playing %s ... ", filename.c_str());

	_video->start();
	while (!shouldQuit() && !_video->endOfVideo()) {
		pollKeyboard();

		if (_video->needsUpdate()) {
			const Graphics::Surface *frame = _video->decodeNextFrame();

			if (frame) {
				_system->copyRectToScreen(frame->getPixels(), frame->pitch, 0, 0, frame->w, frame->h);
				_system->updateScreen();
			}

		}
	}
	_video->close();
}

void ElDoradoEngine::pollKeyboard() {
	Common::Event ev;
	_eventMan->pollEvent(ev);

	if (ev.type != Common::EVENT_KEYDOWN)
		return;

	switch (ev.kbd.keycode) {
		case Common::KEYCODE_ESCAPE:
			debug("Force stop videos");

			if (_video->isPlaying())
				_video->close();
			// quitGame();
		break;
	}
}
 
} // End of namespace ElDorado
