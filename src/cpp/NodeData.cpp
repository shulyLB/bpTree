//
// Created by libao02 on 2022/8/23.
//

#include "../header/NodeItem.h"


NodeData::NodeData(int inKey) : NodeItem(inKey) {}

NodeType NodeData::getNodeType() {
    return Data;
}