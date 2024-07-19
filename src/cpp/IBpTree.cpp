//
// Created by libao02 on 2022/7/29.
//

#include "../header/IBpTree.h"
#include <string>
#include <iostream>

IBpTree::IBpTree(int mm) {
    this->root = nullptr;
    this->max = mm;
    this->count = 0;
    this->high = 0;
}


void IBpTree::put(const int key) {
    // case1 ： 第一个元素
    if (this->root == nullptr) {
        this->root = new BpTreeNode(key, DataNode);
        return;
    }
    BpTreeNode* poped = this->root->put(key, this->high, this->max);
    // 跟节点收到 pop 意味着 树的生长
    if (poped != nullptr) {
        this->high ++;
        auto* newRoot = new BpTreeNode(IndexNode, nullptr, nullptr, 0);
        newRoot->pushBack(new NodeIndex(this->root));
        newRoot->pushBack(new NodeIndex(poped));
        this->root = newRoot;
    }
}


void IBpTree::remove(const int id) {
    if (this->root == nullptr) {
        return;
    }
    unsigned int min =  (this->max >> 1u) + (this->max & 1u);
    this->root->remove(id, this->high, min);
}


int IBpTree::contain(const int id) {
    throw "Not Support";
}


void IBpTree::toString() {
    std::cout << "Deep:=" << this->high << std::endl;
    std::cout << this->Func_toString(this->root, this->high, "") << std::endl;
}

std::string IBpTree::Func_toString(BpTreeNode *findNode, unsigned int findNodeHigh, const std::string& indent) {
    std::string s = "";
    if (findNodeHigh == 0) {
        INodeType *flag = findNode->tail;
        while (flag != nullptr) {
            s += indent + std::to_string(flag->key) + "\n";
            flag = flag->pre;
        }
    } else {
        INodeType *flag = findNode->tail;
        while (flag != nullptr) {
            BpTreeNode *son = ((NodeIndex *)flag)->son;
            s += indent + "(" + std::to_string(flag->key) + ")" + "cnt = " + std::to_string(son->cnt) + "\n";
            s += this->Func_toString(((NodeIndex *) flag)->son, findNodeHigh - 1, indent + "     ");
            flag = flag->pre;
        }
    }
    return s;
}
