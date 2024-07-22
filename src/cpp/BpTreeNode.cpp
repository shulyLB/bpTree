//
// Created by libao02 on 2022/7/29.
//
#include <iostream>
#include <cassert>
#include "../header/BpTreeNode.h"

// 创建一个节点
BpTreeNode::BpTreeNode(int key, NodeType nodeType) {
    if (nodeType == Data) {
        head = tail = new NodeData(key);
    } else {
        head = tail = new NodeIndex(key);
    }
    this->nodeType = nodeType;
    this->cnt = 1;
}

// 拷贝一个节点 ； 多见于分裂 或 合并
BpTreeNode::BpTreeNode(NodeType nodeType, NodeItem *_head, NodeItem *_tail, unsigned int cnt) {
    this->head = _head;
    this->tail = _tail;
    this->nodeType = nodeType;
    this->cnt = cnt;
}

NodeType BpTreeNode::getNodeType() {
    return this->nodeType;
}

int BpTreeNode::getTailValue() {
    return this->tail->key;
}

int BpTreeNode::getHeadValue() {
    return this->head->key;
}

void BpTreeNode::insertBeforeNode(BpTreeNode *root, NodeItem *node, NodeItem *inData) {
    assert(node != nullptr);
    assert(inData != nullptr);

    inData->pre = node->pre;
    inData->next = node;
    node->pre = inData;
    if (inData->pre != nullptr) {
        inData->pre->next = inData;
    }
    if (root->head == node) {
        root->head = inData;
    }
}

void BpTreeNode::insertAfterNode(BpTreeNode *root, NodeItem *node, NodeItem *inData) {
    assert(node != nullptr);
    assert(inData != nullptr);

    inData->next = node->next;
    inData->pre = node;
    node->next = inData;
    if (inData->next != nullptr) {
        inData->next->pre = inData;
    }
    if (root->tail == node) {
        root->tail = inData;
    }
}

void BpTreeNode::insertAfterTailNode(BpTreeNode *root, NodeItem *inData) {
    if (root->head == nullptr) {
        root->head = root->tail = inData;
    } else {
        root->tail->next = inData;
        inData->pre = root->tail;
        root->tail = inData;
    }
    root->cnt++;
}

void BpTreeNode::deleteNode(BpTreeNode *root, NodeItem *node) {
    if (node->pre != nullptr) {
        node->pre->next = node->next;
    } else {
        root->head = node->next;
    }
    if (node->next != nullptr) {
        node->next->pre = node->pre;
    } else {
        root->tail = node->pre;
    }
    // 释放资源
    node->next = node->pre = nullptr;
    switch (node->getNodeType()) {
        case Index:
            delete (NodeIndex*) node;
            break;
        case Data:
            delete (NodeData*) node;
            break;
    }
}
