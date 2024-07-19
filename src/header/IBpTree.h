//
// Created by libao02 on 2022/7/29.
//

#ifndef BPTREE_IBPTREE_H
#define BPTREE_IBPTREE_H

#include "common.h"
#include "BpTreeNode.h"
#include <string>

/**
 *  m = 10 的 B+树
 *      根节点  ： 如果有子女 则最少有两个
 *      非跟结点 ： 最少有5个关键字，
 */
class IBpTree {
private:
    unsigned int max;
    unsigned int high;
    unsigned int count;
    BpTreeNode *root = nullptr;

    std::string Func_toString(BpTreeNode *findNode, unsigned int findNodeHigh, const std::string &indent);

public:
    IBpTree(int mm);

    void put(const int id);

    void remove(const int id);

    int contain(const int id);

    void toString();
};

#endif //BPTREE_IBPTREE_H
