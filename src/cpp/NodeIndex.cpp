//
// Created by libao02 on 2022/8/23.
//

#include "../header/NodeItem.h"

NodeIndex::NodeIndex(int inKey) : NodeItem(inKey) {}

NodeIndex::NodeIndex(BpTreeNode *son) : NodeItem(son->getTailValue()) {
    this->son = son;
}

NodeType NodeIndex::getNodeType() {
    return Index;
}