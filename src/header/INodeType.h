//
// Created by libao02 on 2022/8/23.
//

#ifndef BPTREE_NODE_ITEM_H
#define BPTREE_NODE_ITEM_H

#include "common.h"
#include "BpTreeNode.h"

class INodeType {
    friend class IBpTree;
    friend class BpTreeNode;

protected:
    int key;
    INodeType *next = nullptr;
    INodeType *pre = nullptr;

    /**
     * @param inKey
     * 1. 索引节点代表索引值
     * 2. 数据节点代表存储的数据
     */
    INodeType(int inKey);

    /**
     * @return 节点类型
     */
    virtual NodeType getNodeType() = 0;

    /**
     * 往该节点之前插入元素
     * @param inData
     */
    void insertBefore(INodeType *inData);
    /**
     * 往该节点之后插入元素
     * @param inData
     */
    void insertAfter(INodeType *inData);
};


class NodeIndex : public INodeType {
    friend class IBpTree;
    friend class BpTreeNode;

    BpTreeNode *son = nullptr;

    /**
     * @param inKey
     * 1. 索引节点代表索引值
     */
    NodeIndex(int inKey);

    /**
     * @param son 儿子节点
     */
    NodeIndex(BpTreeNode *son);

    /**
     * @return 节点类型
     */
    virtual NodeType getNodeType();
};

class NodeData : public INodeType {
    friend class IBpTree;

    friend class BpTreeNode;

    /**
     * @param inKey
     * 2. 数据节点代表存储的数据
     */
    NodeData(int inKey);

    /**
     * @return 节点类型
     */
    virtual NodeType getNodeType();

};

#endif //BPTREE_NODELINK_H
