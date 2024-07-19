#include <climits>
//
// Created by libao02 on 2022/7/29.
//

#ifndef BPTREE_BPTREENODE_H
#define BPTREE_BPTREENODE_H

#include "common.h"
#include "INodeType.h"


class BpTreeNode {
private:
    unsigned int cnt;
    NodeType nodeType;
    INodeType *head = nullptr;
    INodeType *tail = nullptr;
protected:
    friend class IBpTree;
    friend class INodeType;
    friend class NodeData;
    friend class NodeIndex;
    // 构造函数 ：新增结点 （估计只有root吧）
    BpTreeNode(int key, NodeType nodeType);
    // 构造函数：分裂结点
    BpTreeNode(NodeType nodeType, INodeType *_head, INodeType *_tail, unsigned int cnt);


    // 结点类型
    NodeType getNodeType();
    // 结点元素最大值
    int getLastValue();
    // 结点元素最大值
    int getFirstValue();

    // 普通放置 需要保证顺序
    BpTreeNode* put(int key, unsigned int h, unsigned int max);
    // 普通删除
    void remove(int key, unsigned int h, unsigned int min);
    // 分裂
    BpTreeNode* split(unsigned int splitLen);
    // 直接后面推入
    void pushBack(INodeType * in);
};

#endif //BPTREE_BPTREENODE_H
