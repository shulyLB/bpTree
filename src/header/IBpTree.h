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
    unsigned int nodeMaxItemCnt;
    unsigned int nodeMinItemCnt;
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

    /**
     * 对于 Tree 的 结点 treeNode 放入数据 key
     */
    static BpTreeNode* TreeNode_put(IBpTree* tree, BpTreeNode* treeNode, int key);

    /**
     * 对于 Tree 的 结点 treeNode 删除数据 key
     */
    static int TreeNode_remove(IBpTree* tree, BpTreeNode* treeNode, int key);

    /**
     * 对于 Tree 的 结点 treeNode 进行分裂，第一个分片的长度为splitLen；
     */
    static BpTreeNode* TreeNode_split(IBpTree* tree, BpTreeNode* treeNode, unsigned int splitLen);
};

#endif //BPTREE_IBPTREE_H
