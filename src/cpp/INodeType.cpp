//
// Created by libao02 on 2022/8/23.
//

#include "../header/INodeType.h"


INodeType::INodeType(int _key) : key(_key) {}

void INodeType::insertBefore(INodeType *inData) {
    inData->pre = this->pre;
    inData->next = this;
    this->pre = inData;
    if (inData->pre != nullptr) {
        inData->pre->next = inData;
    }
}

void INodeType::insertAfter(INodeType *inData) {
    inData->next = this->next;
    inData->pre = this;
    this->next = inData;
    if (inData->next != nullptr) {
        inData->next->pre = inData;
    }
}