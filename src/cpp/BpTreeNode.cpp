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

BpTreeNode::~BpTreeNode() {
    this->cnt = 0;
    this->tail = this->head = nullptr;
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

void BpTreeNode::InsertBeforeNode(BpTreeNode *root, NodeItem *node, NodeItem *inData) {
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
    root->cnt++;
}

void BpTreeNode::InsertAfterNode(BpTreeNode *root, NodeItem *node, NodeItem *inData) {
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
    root->cnt++;
}


void BpTreeNode::PushHead(BpTreeNode *root, NodeItem *inData) {
    inData->next = inData->pre = nullptr;
    if (root->head == nullptr) {
        root->head = root->tail = inData;
    } else {
        root->head->pre = inData;
        inData->next = root->head;
        root->head = inData;
    }
    root->cnt++;
}


void BpTreeNode::PushBack(BpTreeNode *root, NodeItem *inData) {
    inData->next = inData->pre = nullptr;

    if (root->head == nullptr) {
        root->head = root->tail = inData;
    } else {
        root->tail->next = inData;
        inData->pre = root->tail;
        root->tail = inData;
    }
    root->cnt++;
}

NodeItem *BpTreeNode::PopHead(BpTreeNode *root) {
    if (root->head == nullptr) {
        return nullptr;
    }
    if (root->head == root->tail) {
        root->head = root->tail = nullptr;
        root->cnt--;
        return root->head;
    }
    NodeItem *result = root->head;
    root->head = result->next;
    root->head->pre = nullptr;

    result->pre = result->next = nullptr;
    root->cnt--;
    return result;
}

NodeItem *BpTreeNode::PopTail(BpTreeNode *root) {
    if (root->head == nullptr) {
        return nullptr;
    }
    if (root->head == root->tail) {
        root->head = root->tail = nullptr;
        root->cnt--;
        return root->head;
    }
    NodeItem *result = root->tail;
    root->tail = root->tail->pre;
    root->tail->next = nullptr;

    result->pre = result->next = nullptr;
    root->cnt--;
    return result;
}


void BpTreeNode::DeleteNode(BpTreeNode *root, NodeItem *node) {
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
    switch (node->getNodeType()) {
        case Index:
            delete ((NodeIndex *) node);
            break;
        case Data:
            delete ((NodeData *) node);
            break;
    }
    root->cnt--;
}

void BpTreeNode::ClearNode(BpTreeNode *root) {
    if (root == nullptr) {
        return;
    }
    NodeItem *now = root->head;
    while (now != nullptr) {
        NodeItem *needOperator = now;
        now = now->next;

        switch (needOperator->getNodeType()) {
            case Index:
                // 索引节点
                BpTreeNode::ClearNode(((NodeIndex *) needOperator)->son);
                delete ((NodeIndex *) needOperator);
                break;
            case Data:
                // 根节点了
                delete ((NodeData *) needOperator);
                break;
        }
    }
    // 最后释放当前 BpTreeNode
    delete (root);
}


