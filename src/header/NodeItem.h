//
// Created by libao02 on 2022/8/23.
//

#ifndef BPTREE_NODE_ITEM_H
#define BPTREE_NODE_ITEM_H

#include "common.h"
#include "BpTreeNode.h"

class NodeItem {
    friend class IBpTree;
    friend class BpTreeNode;

protected:
    int key;
    NodeItem *next = nullptr;
    NodeItem *pre = nullptr;

    /**
     * @param inKey
     * 1. 索引节点代表索引值
     * 2. 数据节点代表存储的数据
     */
    explicit NodeItem(int inKey);

    /**
     * @return 节点类型
     */
    virtual NodeType getNodeType() = 0;

    /**
     * 往该节点之前插入元素
     * @param inData
     */
    void insertBefore(NodeItem *inData);
    /**
     * 往该节点之后插入元素
     * @param inData
     */
    void insertAfter(NodeItem *inData);
};


class NodeIndex : public NodeItem {
    friend class IBpTree;
    friend class BpTreeNode;

    BpTreeNode *son = nullptr;

    /**
     * @param inKey
     * 1. 索引节点代表索引值
     */
    explicit NodeIndex(int inKey);

    /**
     * @param son 儿子节点
     */
    explicit NodeIndex(BpTreeNode *son);

    /**
     * @return 节点类型
     */
    NodeType getNodeType() override;
};

class NodeData : public NodeItem {
    friend class IBpTree;

    friend class BpTreeNode;

    /**
     * @param inKey
     * 2. 数据节点代表存储的数据
     */
    explicit NodeData(int inKey);

    /**
     * @return 节点类型
     */
    NodeType getNodeType() override;

};

#endif //BPTREE_NODE LINK_H
