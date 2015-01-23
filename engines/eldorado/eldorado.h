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

#ifndef __EL_DORADO_H
#define __EL_DORADO_H

#include "engines/engine.h"


namespace Video {
class VideoDecoder;
}

namespace ElDorado {

class Console;

class ElDoradoEngine : public Engine {
private:
	Video::VideoDecoder *_video;

	void playVideo(const Common::String &filename);

protected:
	void pollKeyboard();

public:
	ElDoradoEngine(OSystem *syst);
	~ElDoradoEngine();

	virtual Common::Error run();
};

} // End of namespace ElDorado

#endif // __EL_DORADO_H
