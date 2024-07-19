#include <climits>
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

BpTreeNode *BpTreeNode::put(BpTreeNode* root, int key, unsigned int max) {
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
        if (key <= insertPosition->key) {
            NodeItem::insertBefore(insertPosition, inLink);
            if (root->head == insertPosition) {
                root->head = inLink;
            }
        } else {
            // 向后插入
            NodeItem::insertAfter(insertPosition, inLink);
            if (root->tail == insertPosition) {
                root->tail = inLink;
            }
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
            NodeItem *link = new NodeIndex(poped);
            // 向后插入
            NodeItem::insertAfter(insertPosition, link);
            if (root->tail == insertPosition) {
                root->tail = link;
            }
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

void BpTreeNode::remove(int key, unsigned int min) {
    // 索引结点
    NodeItem *flag = this->head;
    // 找到 需要插入的 游标地址
    while (flag->next != nullptr) {
        if (key <= flag->key) {
            break;
        }
        flag = flag->next;
    }
    // 无次值
    if (key > flag->key) {
        return;
    }

    if (this->getNodeType() == Data) {
        // TODO
    } else {
        auto *indexFlag = (NodeIndex *) flag;
        BpTreeNode *flagSon = indexFlag->son;
        flagSon->remove(key, min);
        // 需要匀一匀数据；
        if (flagSon->cnt < min) {
            // TODO
            // 1、看前后那个结点可以匀数据出来；如果前后都不够 则和前面的结点合并;
        }
    }
}

BpTreeNode *BpTreeNode::split(BpTreeNode* root, unsigned int splitLen) {
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

void BpTreeNode::pushBack(BpTreeNode* root, NodeItem *in) {
    if (root->head == nullptr) {
        root->head = root->tail = in;
    } else {
        root->tail->next = in;
        in->pre = root->tail;
        root->tail = in;
    }
    root->cnt++;
}