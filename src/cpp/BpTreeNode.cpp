#include <climits>
//
// Created by libao02 on 2022/7/29.
//
#include <iostream>
#include "../header/BpTreeNode.h"

// 创建一个节点
BpTreeNode::BpTreeNode(int key, NodeType nodeType) {
    if (nodeType == DataNode) {
        head = tail = new NodeData(key);
    } else {
        head = tail = new NodeIndex(key);
    }
    this->nodeType = nodeType;
    this->cnt = 1;
}

// 拷贝一个节点 ； 多见于分裂 或 合并
BpTreeNode::BpTreeNode(NodeType nodeType, INodeType *_head, INodeType *_tail, unsigned int cnt) {
    this->head = _head;
    this->tail = _tail;
    this->nodeType = nodeType;
    this->cnt = cnt;
}

NodeType BpTreeNode::getNodeType() {
    return this->nodeType;
}

int BpTreeNode::getLastValue() {
    return this->tail->key;
}

int BpTreeNode::getFirstValue() {
    return this->head->key;
}


BpTreeNode *BpTreeNode::put(int key, unsigned int h, unsigned int max) {
    // 索引结点
    INodeType *insertPosition = this->head;
    // 找到 需要插入的 游标地址
    while (insertPosition != nullptr) {
        // 不允许重复
        if (key == insertPosition->key) {
            return nullptr;
        }
        if (key <= insertPosition->key || insertPosition->next == nullptr) {
            break;
        }
        insertPosition = insertPosition->next;
    }
    // 判断是不是 数据节点 （根据高度等于 0 也是可以的）
    if (this->getNodeType() == DataNode) {
        INodeType *inLink = new NodeData(key);
        // 向前插入
        if (key <= insertPosition->key) {
            insertPosition->insertBefore(inLink);
            if (this->head == insertPosition) {
                this->head = inLink;
            }
        } else {
            // 向后插入
            insertPosition->insertAfter(inLink);
            if (this->tail == insertPosition) {
                this->tail = inLink;
            }
        }
        this->cnt++;
    } else {
        auto *indexFlag = (NodeIndex *) insertPosition;
        BpTreeNode *flagSon = indexFlag->son;
        if (flagSon == nullptr) {
            throw "不可能，索引节点一定有儿子节点";
        }
        BpTreeNode *poped = flagSon->put(key, h - 1, max);
        // 儿子分裂 pop 上来的元素
        if (poped != nullptr) {
            INodeType *link = new NodeIndex(poped);
            // 向后插入
            insertPosition->insertAfter(link);
            if (this->tail == insertPosition) {
                this->tail = link;
            }
            this->cnt++;
        }
        insertPosition->key = flagSon->getLastValue();
    }
    // 分裂成两个并且 给 到父亲节点。
    if (this->cnt > max) {
        unsigned int len = (max >> 1u) + (max & 1u);
        return this->split(len);
    }

    return nullptr;
}

void BpTreeNode::remove(int key, unsigned int h, unsigned int min) {
    // 索引结点
    INodeType *flag = this->head;
    // 找到 需要插入的 游标地址
    while (flag != nullptr) {
        if (key <= flag->key || flag->next == nullptr) {
            break;
        }
        flag = flag->next;
    }
    if (this->getNodeType() == DataNode) {
//        flag->remove();
    } else {
//        auto *indexFlag = (BpTreeIndexLink *) flag;
//        BpTreeNode *flagSon = indexFlag->son;
//        flagSon->remove(key, h - 1, min);
    }
}

BpTreeNode *BpTreeNode::split(unsigned int splitLen) {
    if (splitLen < 1 || splitLen > this->cnt) {
        throw "分裂长度不对";
    }

    INodeType *splitPosition = this->head;
    for (int step = 0; step < splitLen && splitPosition != nullptr; step++, splitPosition = splitPosition->next);

    INodeType *newHead = splitPosition;
    INodeType *newTail = this->tail;

    this->tail = newHead->pre;

    newHead->pre->next = nullptr;
    newHead->pre = nullptr;
    auto *newRoot = new BpTreeNode(this->nodeType, newHead, newTail, this->cnt - splitLen);
    this->cnt = splitLen;
    return newRoot;
}

void BpTreeNode::pushBack(INodeType *in) {
    if (this->head == nullptr) {
        this->head = this->tail = in;
    } else {
        this->tail->next = in;
        in->pre = this->tail;
        this->tail = in;
    }
    this->cnt++;
}