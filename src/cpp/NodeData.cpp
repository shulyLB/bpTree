//
// Created by libao02 on 2022/8/23.
//

#include "../header/INodeType.h"


NodeData::NodeData(int inKey) : INodeType(inKey) {}

NodeType NodeData::getNodeType() {
    return DataNode;
}