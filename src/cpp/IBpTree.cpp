//
// Created by libao02 on 2022/7/29.
//

#include "../header/IBpTree.h"
#include <string>
#include <iostream>

IBpTree::IBpTree(int mm) {
    this->root = nullptr;
    this->nodeMaxItemCnt = mm;
    this->nodeMinItemCnt = (mm >> 1u) + (mm & 1u);
    this->dataCount = 0;
    this->high = 0;
}


void IBpTree::put(int key) {
    // case1 ： 第一个元素
    if (this->root == nullptr) {
        this->root = new BpTreeNode(key, Data);
        return;
    }
    BpTreeNode *bePopData = BpTreeNode::put(this->root, key, this->nodeMaxItemCnt);
    // 跟节点收到 pop 意味着 树的生长
    if (bePopData != nullptr) {
        this->high++;
        auto *newRoot = new BpTreeNode(Index, nullptr, nullptr, 0);
        BpTreeNode::pushBack(newRoot, new NodeIndex(this->root));
        BpTreeNode::pushBack(newRoot, new NodeIndex(bePopData));
        this->root = newRoot;
    }
}


void IBpTree::remove(int id) {
    if (this->root == nullptr) {
        return;
    }
    this->root->remove(id, this->nodeMinItemCnt);
}


int IBpTree::contain(int id) {
    throw "Not Support";
}


void IBpTree::toString() {
    std::cout << "Deep:=" << this->high << std::endl;
    std::cout << this->Func_toString(this->root, this->high, "") << std::endl;
}

std::string IBpTree::Func_toString(BpTreeNode *findNode, unsigned int findNodeHigh, const std::string &indent) {
    std::string s = "";
    if (findNodeHigh == 0) {
        NodeItem *flag = findNode->tail;
        while (flag != nullptr) {
            s += indent + std::to_string(flag->key) + "\n";
            flag = flag->pre;
        }
    } else {
        NodeItem *flag = findNode->tail;
        while (flag != nullptr) {
            BpTreeNode *son = ((NodeIndex *) flag)->son;
            s += indent + "(" + std::to_string(flag->key) + ")" + "cnt = " + std::to_string(son->cnt) + "\n";
            s += this->Func_toString(((NodeIndex *) flag)->son, findNodeHigh - 1, indent + "     ");
            flag = flag->pre;
        }
    }
    return s;
}
