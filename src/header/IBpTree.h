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
    /**
     * 核心参数每个结点最大的数据数量；
     * 同时 非 跟结点的 最小数据数量 是  nodeMaxDataCnt >> 1
     */
    unsigned int nodeMaxDataCnt;
    unsigned int high;
    unsigned int dataCount;
    BpTreeNode *root = nullptr;
    std::string Func_toString(BpTreeNode *findNode, unsigned int findNodeHigh, const std::string &indent);

public:
    explicit IBpTree(int mm);

    void put(int id);

    void remove(int id);

    int contain(int id);

    void toString();
};

#endif //BPTREE_IBPTREE_H
