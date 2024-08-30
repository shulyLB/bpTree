//
// Created by libao02 on 2022/7/29.
//

#ifndef BPTREE_IBPTREE_H
#define BPTREE_IBPTREE_H

#include "common.h"
#include "BpTreeNode.h"
#include <string>
#include "IException.h"

/**
 *  m = 10 的 B+树
 *      根节点  ： 如果有子女 则最少有两个
 *      非跟结点 ： 最少有5个关键字，
 */
class IBpTree {
private:
    unsigned int nodeMaxItemCnt;
    unsigned int nodeMinItemCnt;
    int high;
    unsigned int dataCount;
    BpTreeNode *root = nullptr;
    static std::string Func_toString(BpTreeNode *findNode, unsigned int findNodeHigh, const std::string &indent);

    /**
     * 对于 Tree 的 结点 treeNode 放入数据 key
     */
    static int TreeNode_put(IBpTree* tree, BpTreeNode* treeNode, int key);

    /**
     * 对于 Tree 的 结点 treeNode 删除数据 key
     */
    static int TreeNode_remove(IBpTree* tree, BpTreeNode* treeNode, int key);

    /**
     * 对于 Tree 的 结点 treeNode 进行分裂，第一个分片的长度为splitLen；
     */
    static BpTreeNode* TreeNode_split(IBpTree* tree, BpTreeNode* treeNode, unsigned int splitLen);

    /**
     * Tree 的 结点 treeNode 的 儿子结点 lSon 和 rSon 进行合并（lSon 和 rSon 必然相邻）
     */
    static void TreeNode_merge(IBpTree *tree, BpTreeNode *treeNode, NodeIndex *lSon, NodeIndex *rSon);
public:
    explicit IBpTree(int mm);

    ~IBpTree();

    int put(int id);

    void remove(int id);

    int contain(int id);

    void toString();
};

#endif //BPTREE_IBPTREE_H
