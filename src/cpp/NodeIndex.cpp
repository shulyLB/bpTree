//
// Created by libao02 on 2022/8/23.
//

#include "../header/INodeType.h"

NodeIndex::NodeIndex(int inKey) : INodeType(inKey) {}

NodeIndex::NodeIndex(BpTreeNode *son) : INodeType(son->getLastValue()) {
    this->son = son;
}

NodeType NodeIndex::getNodeType() {
    return IndexNode;
}