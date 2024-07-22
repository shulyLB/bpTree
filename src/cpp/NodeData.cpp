//
// Created by libao02 on 2022/8/23.
//

#include "../header/NodeItem.h"


NodeData::NodeData(int inKey) : NodeItem(inKey) {}

NodeData::~NodeData() {
    this->pre = this->next = nullptr;
}

NodeType NodeData::getNodeType() {
    return Data;
}

