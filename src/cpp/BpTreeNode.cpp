//
// Created by libao02 on 2022/7/29.
//
#include <iostream>
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

BpTreeNode *BpTreeNode::put(BpTreeNode *root, int key, unsigned int max) {
    // 索引结点
    NodeItem *insertPosition = root->head;
    // 找到 需要插入的 游标地址
    while (insertPosition->next != nullptr) {
        if (key <= insertPosition->key) {
            break;
        }
        insertPosition = insertPosition->next;
    }
    if (root->getNodeType() == Data) {
        // 数据插入 => 数据结点
        NodeItem *inLink = new NodeData(key);
        // 向前插入
        if (key < insertPosition->key) {
            BpTreeNode::insertBeforeNode(root, insertPosition, inLink);
        } else if (key > insertPosition->key) {
            BpTreeNode::insertAfterNode(root, insertPosition, inLink);
        } else {
            // 不允许重复
            return nullptr;
        }
        root->cnt++;
    } else {
        // 数据插入 => 索引结点
        auto *indexFlag = (NodeIndex *) insertPosition;
        BpTreeNode *flagSon = indexFlag->son;
        if (flagSon == nullptr) {
            throw "不可能，索引节点一定有儿子节点";
        }
        BpTreeNode *poped = BpTreeNode::put(flagSon, key, max);
        // 儿子分裂 pop 上来的元素
        if (poped != nullptr) {
            NodeItem *inLink = new NodeIndex(poped);
            BpTreeNode::insertAfterNode(root, insertPosition, inLink);
            root->cnt++;
        }
        // 更正索引的值
        insertPosition->key = flagSon->getTailValue();
    }
    // 分裂成两个并且 给 到父亲节点。
    if (root->cnt > max) {
        unsigned int len = (max >> 1u) + (max & 1u);
        return BpTreeNode::split(root, len);
    }
    return nullptr;
}

int BpTreeNode::remove(BpTreeNode *root, int key, unsigned int min) {
    // 索引结点
    NodeItem *deletePosition = root->head;
    // 找到 需要插入的 游标地址
    while (deletePosition->next != nullptr) {
        if (key <= deletePosition->key) {
            break;
        }
        deletePosition = deletePosition->next;
    }
    // 无此值
    if (key > deletePosition->key) {
        return 0;
    }
    if (root->getNodeType() == Data) {
        // 删除该值
        if (key == deletePosition->key) {
            BpTreeNode::deleteNode(root, deletePosition);
        } else {
            return 0;
        }
    } else {
        auto *indexFlag = (NodeIndex *) deletePosition;
        BpTreeNode *flagSon = indexFlag->son;
        BpTreeNode::remove(flagSon, key, min);
        // 需要匀一匀数据；
        if (flagSon->cnt < min) {
            // TODO
            // 1、看前后那个结点可以匀数据出来；如果前后都不够 则和前面的结点合并;
        }
    }
}

BpTreeNode *BpTreeNode::split(BpTreeNode *root, unsigned int splitLen) {
    if (splitLen < 1 || splitLen > root->cnt) {
        throw "分裂长度不对";
    }

    NodeItem *splitPosition = root->head;
    for (int step = 0; step < splitLen && splitPosition != nullptr; step++, splitPosition = splitPosition->next);

    NodeItem *newHead = splitPosition;
    NodeItem *newTail = root->tail;

    root->tail = newHead->pre;

    newHead->pre->next = nullptr;
    newHead->pre = nullptr;
    auto *newRoot = new BpTreeNode(root->nodeType, newHead, newTail, root->cnt - splitLen);
    root->cnt = splitLen;
    return newRoot;
}

void BpTreeNode::pushBack(BpTreeNode *root, NodeItem *in) {
    if (root->head == nullptr) {
        root->head = root->tail = in;
    } else {
        root->tail->next = in;
        in->pre = root->tail;
        root->tail = in;
    }
    root->cnt++;
}

void BpTreeNode::insertBeforeNode(BpTreeNode *root, NodeItem *node, NodeItem *inData) {
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
