//
// Created by libao02 on 2022/8/23.
//

#include "../header/NodeItem.h"


NodeItem::NodeItem(int _key) : key(_key) {}


void NodeItem::insertBefore(NodeItem *node, NodeItem *inData) {
    inData->pre = node->pre;
    inData->next = node;
    node->pre = inData;
    if (inData->pre != nullptr) {
        inData->pre->next = inData;
    }
}

void NodeItem::insertAfter(NodeItem *node, NodeItem *inData) {
    inData->next = node->next;
    inData->pre = node;
    node->next = inData;
    if (inData->next != nullptr) {
        inData->next->pre = inData;
    }
}

