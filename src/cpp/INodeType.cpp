//
// Created by libao02 on 2022/8/23.
//

#include "../header/NodeItem.h"


NodeItem::NodeItem(int _key) : key(_key) {}

void NodeItem::insertBefore(NodeItem *inData) {
    inData->pre = this->pre;
    inData->next = this;
    this->pre = inData;
    if (inData->pre != nullptr) {
        inData->pre->next = inData;
    }
}

void NodeItem::insertAfter(NodeItem *inData) {
    inData->next = this->next;
    inData->pre = this;
    this->next = inData;
    if (inData->next != nullptr) {
        inData->next->pre = inData;
    }
}