/*
 Copyright (C) 2010-2012 Kristian Duske
 
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
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TrenchBroom_Octree_h
#define TrenchBroom_Octree_h

#include <vector>
#include "VecMath.h"
#include "Map.h"
#include "MapObject.h"
#include "Observer.h"

using namespace std;

namespace TrenchBroom {
    namespace Model {
        typedef enum {
            CP_WSB = 0,
            CP_WST = 1,
            CP_WNB = 2,
            CP_WNT = 3,
            CP_ESB = 4,
            CP_EST = 5,
            CP_ENB = 6,
            CP_ENT = 7
        } ENodePosition;
        
        class OctreeNode {
        private:
            int m_minSize;
            BBox m_bounds;
            vector<MapObject&> m_objects;
            OctreeNode* m_children[8];
            bool addObject(MapObject& object, int childIndex);
        public:
            OctreeNode(BBox bounds, int minSize);
            ~OctreeNode();
            bool addObject(MapObject& object);
            bool removeObject(MapObject& object);
            void intersect(TRay ray, vector<Map::MapObject&>& objects);
        };
        
        class Map;
        class Octree : public Observer {
        private:
            int m_minSize;
            Map* m_map;
            OctreeNode* m_root;
        protected:
            void notify(const string &name, const void *data);
        public:
            Octree(Map* map, int minSize);
            ~Octree();
            vector<MapObject&> intersect(TRay ray);
        };
    }
}
#endif
