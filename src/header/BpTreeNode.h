#include <climits>
//
// Created by libao02 on 2022/7/29.
//

#ifndef BPTREE_BPTREENODE_H
#define BPTREE_BPTREENODE_H

#include "common.h"
#include "NodeItem.h"


class BpTreeNode {
private:
    unsigned int cnt;
    NodeType nodeType;
    NodeItem *head = nullptr;
    NodeItem *tail = nullptr;
protected:
    friend class IBpTree;
    friend class NodeItem;
    friend class NodeData;
    friend class NodeIndex;
    // 构造函数 ：新增结点 （估计只有root吧）
    BpTreeNode(int key, NodeType nodeType);
    // 构造函数：分裂结点
    BpTreeNode(NodeType nodeType, NodeItem *_head, NodeItem *_tail, unsigned int cnt);

    // 结点类型
    NodeType getNodeType();
    // 结点元素最大值
    int getTailValue();
    // 结点元素最小值
    int getHeadValue();
    /**
     * @param key 放入的Key
     * @param max 结点存储的最大值
     * @return 返回的值如果不是 nullptr 则证明当前结点分裂成了连个
     */
    static BpTreeNode* put(BpTreeNode* root, int key, unsigned int max);
    // 普通删除
    static void remove(BpTreeNode* root, int key, unsigned int min);
    // 分裂
    static BpTreeNode* split(BpTreeNode* root, unsigned int splitLen);
    // 直接后面推入
    static void pushBack(BpTreeNode* root, NodeItem * in);
};

#endif //BPTREE_BPTREENODE_H
