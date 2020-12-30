/*
 Copyright (C) 2020 Kristian Duske

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

#include "Model/GroupNode.h"
#include "View/MapDocumentTest.h"
#include "View/MapDocument.h"

#include "Catch2.h"

namespace TrenchBroom {
    namespace View {
        class AddNodesTest : public MapDocumentTest {};

        TEST_CASE_METHOD(AddNodesTest, "AddNodesTest.connectAddedSingletonGroups") {
            Model::GroupNode* group = new Model::GroupNode(Model::Group("group"));
            
            const auto initiallyConnected = GENERATE(true, false);

            if (!initiallyConnected) {
                group->disconnectFromLinkSet();
            }

            document->addNode(group, document->parentForNodes());
            CHECK(group->connectedToLinkSet());

            document->undoCommand();
            CHECK_FALSE(group->connectedToLinkSet());
        }

        TEST_CASE_METHOD(AddNodesTest, "AddNodesTest.recursivelyConnectAddedSingletonGroups") {
            Model::GroupNode* outer = new Model::GroupNode(Model::Group("outer"));
            Model::GroupNode* inner = new Model::GroupNode(Model::Group("inner"));
            outer->addChild(inner);

            const auto outerGroupInitiallyConnected = GENERATE(true, false);
            const auto innerGroupInitiallyConnected = GENERATE(true, false);

            if (!outerGroupInitiallyConnected) {
                outer->disconnectFromLinkSet();
            }
            if (!innerGroupInitiallyConnected) {
                inner->disconnectFromLinkSet();
            }
            
            document->addNode(outer, document->parentForNodes());
            CHECK(outer->connectedToLinkSet());
            CHECK(inner->connectedToLinkSet());

            document->undoCommand();
            CHECK_FALSE(outer->connectedToLinkSet());
            CHECK_FALSE(inner->connectedToLinkSet());
        }
    }
}
