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
     * 在 root这个树结点，于node之后插接 inData
     */
    static void InsertBeforeNode(BpTreeNode* root, NodeItem *node, NodeItem *inData);

    /**
     * 在 root这个树结点，于node之前插接 inData
     */
    static void InsertAfterNode(BpTreeNode* root, NodeItem *node, NodeItem *inData);

    /**
     * 在 root这个树结点，删除node
     */
    static void DeleteNode(BpTreeNode* root, NodeItem *node);

    /**
     * 在 root这个树结点的尾部，插入 inData
     */
    static void PushBack(BpTreeNode* root, NodeItem * inData);

    static NodeItem * PopHead(BpTreeNode* root);
};

#endif //BPTREE_BPTREENODE_H
