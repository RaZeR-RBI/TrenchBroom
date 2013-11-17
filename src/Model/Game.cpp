/*
 Copyright (C) 2010-2013 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Game.h"

#include "Model/GameFactory.h"

namespace TrenchBroom {
    namespace Model {
        Game::~Game() {}

        const String& Game::gameName() const {
            return doGameName();
        }

        bool Game::isGamePathPreference(const IO::Path& prefPath) const {
            const GameFactory& gameFactory = GameFactory::instance();
            return gameFactory.isGamePathPreference(gameName(), prefPath);
        }

        void Game::setGamePath(const IO::Path& gamePath) {
            doSetGamePath(gamePath);
        }

        void Game::setAdditionalSearchPaths(const IO::Path::List& searchPaths) {
            doSetAdditionalSearchPaths(searchPaths);
        }

        Map* Game::newMap(const MapFormat::Type format) const {
            return doNewMap(format);
        }
        
        Map* Game::loadMap(const BBox3& worldBounds, const IO::Path& path) const {
            return doLoadMap(worldBounds, path);
        }
        
        Model::EntityList Game::parseEntities(const BBox3& worldBounds, const String& str) const {
            return doParseEntities(worldBounds, str);
        }
        
        Model::BrushList Game::parseBrushes(const BBox3& worldBounds, const String& str) const {
            return doParseBrushes(worldBounds, str);
        }
        
        Model::BrushFaceList Game::parseFaces(const BBox3& worldBounds, const String& str) const {
            return doParseFaces(worldBounds, str);
        }
        
        void Game::writeMap(Map& map, const IO::Path& path) const {
            doWriteMap(map, path);
        }
        
        void Game::writeObjectsToStream(const MapFormat::Type format, const Model::ObjectList& objects, std::ostream& stream) const {
            doWriteObjectsToStream(format, objects, stream);
        }
        
        void Game::writeFacesToStream(const MapFormat::Type format, const Model::BrushFaceList& faces, std::ostream& stream) const {
            doWriteFacesToStream(format, faces, stream);
        }
        
        IO::Path::List Game::findBuiltinTextureCollections() const {
            return doFindBuiltinTextureCollections();
        }
        
        IO::Path::List Game::extractTexturePaths(const Map* map) const {
            return doExtractTexturePaths(map);
        }
        
        Assets::TextureCollection* Game::loadTextureCollection(const IO::Path& path) const {
            return doLoadTextureCollection(path);
        }
        
        Assets::EntityDefinitionList Game::loadEntityDefinitions(const IO::Path& path) const {
            return doLoadEntityDefinitions(path);
        }
        
        IO::Path Game::defaultEntityDefinitionFile() const {
            return doDefaultEntityDefinitionFile();
        }
        
        IO::Path Game::extractEntityDefinitionFile(const Map* map) const {
            return doExtractEntityDefinitionFile(map);
        }
        
        Assets::EntityModel* Game::loadModel(const IO::Path& path) const {
            return doLoadModel(path);
        }

        StringList Game::availableMods() const {
            return doAvailableMods();
        }

        StringList Game::extractEnabledMods(const Map* map) const {
            return doExtractEnabledMods(map);
        }
    }
}
