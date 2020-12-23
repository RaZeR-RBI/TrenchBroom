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

#include "Model/EntityNode.h"
#include "Model/GroupNode.h"

#include <vecmath/bbox.h>
#include <vecmath/bbox_io.h>

#include <memory>
#include <vector>

#include "Catch2.h"

namespace TrenchBroom {
    namespace Model {
        TEST_CASE("GroupNodeTest.constructor", "[GroupNodeTest]") {
            auto groupNode = GroupNode(Group("name"));
            CHECK(groupNode.connectedToLinkSet());
            CHECK_THAT(groupNode.linkedGroups(), Catch::UnorderedEquals(std::vector<GroupNode*>{&groupNode}));
        }

        TEST_CASE("GroupNodeTest.clone", "[GroupNodeTest]") {
            const auto worldBounds = vm::bbox3d(8192.0);
            auto groupNode = GroupNode(Group("name"));
            
            auto groupNodeClone = std::unique_ptr<GroupNode>{static_cast<GroupNode*>(groupNode.clone(worldBounds))};
            CHECK_FALSE(inSameLinkSet(groupNode, *groupNodeClone));
        }

        TEST_CASE("GroupNodeTest.cloneRecursively", "[GroupNodeTest]") {
            const auto worldBounds = vm::bbox3d(8192.0);
            auto groupNode = GroupNode(Group("name"));
            
            auto groupNodeClone = std::unique_ptr<GroupNode>{static_cast<GroupNode*>(groupNode.cloneRecursively(worldBounds))};
            CHECK_FALSE(inSameLinkSet(groupNode, *groupNodeClone));
        }

        TEST_CASE("GroupNodeTest.inSameLinkSet", "[GroupNodeTest]") {
            const auto worldBounds = vm::bbox3d(8192.0);
            
            auto groupNode = GroupNode(Group("name"));
            CHECK(inSameLinkSet(groupNode, groupNode));

            auto* entityNode = new EntityNode();
            groupNode.addChild(entityNode);
            REQUIRE(groupNode.childCount() == 1u);

            auto groupNodeClone = std::unique_ptr<GroupNode>{static_cast<GroupNode*>(groupNode.cloneRecursively(worldBounds))};
            CHECK_FALSE(inSameLinkSet(groupNode, *groupNodeClone));
            CHECK_FALSE(inSameLinkSet(*groupNodeClone, groupNode));
            groupNode.addToLinkSet(*groupNodeClone);
            CHECK(inSameLinkSet(groupNode, *groupNodeClone));
            CHECK(inSameLinkSet(*groupNodeClone, groupNode));

            auto otherGroupNode = GroupNode(Group("other"));
            CHECK_FALSE(inSameLinkSet(otherGroupNode, groupNode));
            CHECK_FALSE(inSameLinkSet(groupNode, otherGroupNode));
            CHECK_FALSE(inSameLinkSet(otherGroupNode, *groupNodeClone));
            CHECK_FALSE(inSameLinkSet(*groupNodeClone, otherGroupNode));
        }

        TEST_CASE("GroupNodeTest.addToLinkSet", "[GroupNodeTest]") {
            const auto worldBounds = vm::bbox3d(8192.0);
            
            auto groupNode = GroupNode(Group("name"));
            auto* entityNode = new EntityNode();
            groupNode.addChild(entityNode);
            REQUIRE(groupNode.childCount() == 1u);
            
            auto groupNodeClone = std::unique_ptr<GroupNode>{static_cast<GroupNode*>(groupNode.cloneRecursively(worldBounds))};
            REQUIRE_FALSE(inSameLinkSet(*groupNodeClone, groupNode));
            REQUIRE(groupNodeClone->connectedToLinkSet());

            groupNode.addToLinkSet(*groupNodeClone);
            CHECK(inSameLinkSet(*groupNodeClone, groupNode));
            CHECK(groupNodeClone->connectedToLinkSet());
        }

        TEST_CASE("GroupNodeTest.connectToLinkSet", "[GroupNodeTest]") {
            auto groupNode = GroupNode(Group("name"));
            groupNode.disconnectFromLinkSet();
            REQUIRE_FALSE(groupNode.connectedToLinkSet());
            REQUIRE_THAT(groupNode.linkedGroups(), Catch::UnorderedEquals(std::vector<GroupNode*>{}));

            groupNode.connectToLinkSet();
            CHECK(groupNode.connectedToLinkSet());
            CHECK_THAT(groupNode.linkedGroups(), Catch::UnorderedEquals(std::vector<GroupNode*>{&groupNode}));
        }

        TEST_CASE("GroupNodeTest.disconnectFromLinkSet", "[GroupNodeTest]") {
            auto groupNode = GroupNode(Group("name"));
            REQUIRE(groupNode.connectedToLinkSet());
            REQUIRE_THAT(groupNode.linkedGroups(), Catch::UnorderedEquals(std::vector<GroupNode*>{&groupNode}));

            groupNode.disconnectFromLinkSet();
            CHECK_FALSE(groupNode.connectedToLinkSet());
            CHECK_THAT(groupNode.linkedGroups(), Catch::UnorderedEquals(std::vector<GroupNode*>{}));
        }
    }
}
