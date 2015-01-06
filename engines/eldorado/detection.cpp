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
#include "eldorado/eldorado.h"
 
#include "common/config-manager.h"
#include "common/error.h"
#include "common/fs.h"
 
#include "engines/metaengine.h"

static const PlainGameDescriptor eldorado_setting[] = {
	{ "eldorado", "Road To El Dorado (Windows/English)" },
	{ 0, 0 }
};

class ElDoradoMetaEngine : public MetaEngine {
public:
	virtual const char *getName() const {
		return "ElDorado Engine";
	}

	virtual const char *getOriginalCopyright() const {
		return "El Dorado (C)2000 Revolution Software Ltd";
	}

	virtual GameList getSupportedGames() const {
		GameList games;
		const PlainGameDescriptor *g = eldorado_setting;
		while (g->gameid) {
			games.push_back(*g);
			g++;
		}

		return games;
	}

	virtual GameDescriptor findGame(const char *gameid) const {
		const PlainGameDescriptor *g = eldorado_setting;
		while (g->gameid) {
			if (0 == scumm_stricmp(gameid, g->gameid))
				break;
			g++;
		}
		return GameDescriptor(g->gameid, g->description);
	}

	virtual GameList detectGames(const Common::FSList &fslist) const {
		GameList detectedGames;

		// Iterate over all files in the given directory
		for (Common::FSList::const_iterator file = fslist.begin(); file != fslist.end(); ++file) {
			if (!file->isDirectory()) {
				const char *gameName = file->getName().c_str();

				if (0 == scumm_stricmp("neumevb.oft", gameName)) {
					// You could check the contents of the file now if you need to.
					detectedGames.push_back(eldorado_setting[0]);
					break;
				}
			}
		}
		return detectedGames;
	}

	virtual Common::Error createInstance(OSystem *syst, Engine **engine) const {
		assert(syst);
		assert(engine);

		// Scan the target directory for files (error out if it does not exist)
		Common::FSList fslist;
		Common::FSNode dir(ConfMan.get("path"));
		if (!dir.getChildren(fslist, Common::FSNode::kListAll)) {
			return Common::kNoGameDataFoundError;
		}

		// Invoke the detector
		Common::String gameid = ConfMan.get("gameid");
		GameList detectedGames = detectGames(fslist);

		for (uint i = 0; i < detectedGames.size(); i++) {
			if (detectedGames[i].gameid() == gameid) {
				// At this point you may want to perform additional sanity checks.
				*engine = new ElDorado::ElDoradoEngine(syst);
				return Common::kNoError;
			}
		}

		// Failed to find any game data
		return Common::kNoGameDataFoundError;
	}
};
 
#if PLUGIN_ENABLED_DYNAMIC(ELDORADO)
	REGISTER_PLUGIN_DYNAMIC(ELDORADO, PLUGIN_TYPE_ENGINE, ElDoradoMetaEngine);
#else
	REGISTER_PLUGIN_STATIC(ELDORADO, PLUGIN_TYPE_ENGINE, ElDoradoMetaEngine);
#endif
