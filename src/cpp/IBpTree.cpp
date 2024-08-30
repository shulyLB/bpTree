//
// Created by libao02 on 2022/7/29.
//

#include "../header/IBpTree.h"
#include <string>
#include <iostream>

IBpTree::IBpTree(int mm) {
    if (mm < 5) {
        throw IException(ERROR_INIT_ILLEGAL_NODE_NUMBER_ERROR);
    }
    this->root = nullptr;
    this->nodeMaxItemCnt = mm;
    this->nodeMinItemCnt = (mm >> 1u);
    this->dataCount = 0;
    this->high = 0;
}

IBpTree::~IBpTree() {
    // TODO
}

int IBpTree::put(int key) {
    // case1 ： 第一个元素
    if (this->root == nullptr) {
        this->root = new BpTreeNode(key, Data);
        this->dataCount ++;
        return 1;
    }
    int result = IBpTree::TreeNode_put(this, this->root, key);

    if (this->root->cnt > this->nodeMaxItemCnt) {
        BpTreeNode *inNode = IBpTree::TreeNode_split(this, this->root, this->nodeMinItemCnt);

        this->high++;
        auto *newRoot = new BpTreeNode(Index, nullptr, nullptr, 0);
        BpTreeNode::PushBack(newRoot, new NodeIndex(this->root));
        BpTreeNode::PushBack(newRoot, new NodeIndex(inNode));
        this->root = newRoot;
    }
    this->dataCount += result;
    return result;
}

void IBpTree::remove(int id) {
    if (this->root == nullptr) {
        return;
    }
    int result = IBpTree::TreeNode_remove(this, this->root, id);
    // 如果跟结点是索引节点，则最少有两个孩子; 树被砍伐了
    if (this->root->getNodeType() == Index && this->root->cnt == 1) {
        // 直接砍掉根
        NodeIndex *onlyItem = ((NodeIndex *) this->root->head);
        BpTreeNode *needDeleteNode = this->root;
        this->root = onlyItem->son;
        this->high--;

        // 释放资源 (head 和 tail 是一个节点)
        delete ((NodeIndex *) needDeleteNode->head);
        delete needDeleteNode;
    }
    this->dataCount -= result;
}

int IBpTree::contain(int id) {
    BpTreeNode *treeNode = this->root;
    while (treeNode->getNodeType() != Data) {
        // 索引结点
        NodeItem *queryPosition = treeNode->head;
        while (queryPosition->next != nullptr) {
            if (id <= queryPosition->key) {
                break;
            }
            queryPosition = queryPosition->next;
        }
        if (id > queryPosition->key) {
            return -1;
        }
        treeNode = ((NodeIndex *) queryPosition)->son;
    }

    NodeItem *queryPosition = treeNode->head;
    while (queryPosition->next != nullptr) {
        if (id <= queryPosition->key) {
            break;
        }
        queryPosition = queryPosition->next;
    }
    if (id != queryPosition->key) {
        return -1;
    } else {
        return id;
    }


}

void IBpTree::toString() {
    std::cout << "Deep:=" << this->high << ";" << "Cnt:=" << this->dataCount << std::endl;
    std::cout << IBpTree::Func_toString(this->root, this->high, "") << std::endl;
}

std::string IBpTree::Func_toString(BpTreeNode *findNode, unsigned int findNodeHigh, const std::string &indent) {
    std::string s = std::string("");
    if (findNodeHigh == 0) {
        NodeItem *flag = findNode->tail;
        while (flag != nullptr) {
            s += indent + std::to_string(flag->key) + "\n";
            flag = flag->pre;
        }
    } else {
        NodeItem *flag = findNode->tail;
        while (flag != nullptr) {
            BpTreeNode *son = ((NodeIndex *) flag)->son;
            s += indent + "(" + std::to_string(flag->key) + ")" + "cnt = " + std::to_string(son->cnt) + "\n";
            s += IBpTree::Func_toString(((NodeIndex *) flag)->son, findNodeHigh - 1, indent + "     ");
            flag = flag->pre;
        }
    }
    return s;
}

int IBpTree::TreeNode_put(IBpTree *tree, BpTreeNode *treeNode, int key) {
    // 索引结点
    NodeItem *insertPosition = treeNode->head;
    // 找到 需要插入的 游标地址
    while (insertPosition->next != nullptr) {
        if (key <= insertPosition->key) {
            break;
        }
        insertPosition = insertPosition->next;
    }
    if (treeNode->getNodeType() == Data) {
        // 数据插入 => 数据结点
        NodeItem *inLink = new NodeData(key);
        // 向前插入
        if (key < insertPosition->key) {
            BpTreeNode::InsertBeforeNode(treeNode, insertPosition, inLink);
            return 1;
        } else if (key > insertPosition->key) {
            BpTreeNode::InsertAfterNode(treeNode, insertPosition, inLink);
            return 1;
        } else {
            // 不允许重复
            return 0;
        }
    } else {
        // 数据插入 => 索引结点
        auto *indexFlag = (NodeIndex *) insertPosition;
        BpTreeNode *insertNode = indexFlag->son;
        if (insertNode == nullptr) {
            throw IException(ERROR_WHEN_INSERT_INDEX_NO_HAVE_SON);
        }
        int result = IBpTree::TreeNode_put(tree, insertNode, key);
        if (insertNode->cnt > tree->nodeMaxItemCnt) {
            BpTreeNode *inNode = IBpTree::TreeNode_split(tree, insertNode, tree->nodeMinItemCnt);
            BpTreeNode::InsertAfterNode(treeNode, insertPosition, new NodeIndex(inNode));
            insertPosition->key = insertNode->getTailValue();
        }
        return result;
    }
}

int IBpTree::TreeNode_remove(IBpTree *tree, BpTreeNode *treeNode, int key) {
    // 索引结点
    NodeItem *deletePosition = treeNode->head;
    // 找到 需要插入的 游标地址
    while (deletePosition->next != nullptr) {
        if (key <= deletePosition->key) {
            break;
        }
        deletePosition = deletePosition->next;
    }
    // @Case 这个结点的值 比 目标值效
    if (key > deletePosition->key) {
        return 0;
    }
    if (treeNode->getNodeType() == Data) {
        // 删除该值
        if (key == deletePosition->key) {
            BpTreeNode::DeleteNode(treeNode, deletePosition);
            return 1;
        }
        return 0;
    }
    auto *realDeleteNode = (NodeIndex *) deletePosition;
    BpTreeNode *deleteSon = realDeleteNode->son;
    int result = IBpTree::TreeNode_remove(tree, deleteSon, key);
    // 当前结点数据不够了，需要进行处理
    if (deleteSon->cnt < tree->nodeMinItemCnt) {
        // 1、看看删除结点的后面数据是否可以借用
        auto deleteNextNode = (NodeIndex *) realDeleteNode->next;
        if (deleteNextNode != nullptr && deleteNextNode->son->cnt > tree->nodeMinItemCnt) {
            NodeItem *popNodeItem = BpTreeNode::PopHead(deleteNextNode->son);
            BpTreeNode::PushBack(deleteSon, popNodeItem);
            realDeleteNode->key = realDeleteNode->son->getTailValue();
            return result;
        }
        // 2、看看删除结点的前面数据是否可以借用
        auto deletePreNode = (NodeIndex *) realDeleteNode->pre;
        if (deletePreNode != nullptr && deletePreNode->son->cnt > tree->nodeMinItemCnt) {
            NodeItem *popNodeItem = BpTreeNode::PopTail(deletePreNode->son);
            BpTreeNode::PushHead(deleteSon, popNodeItem);
            deletePreNode->key = deletePreNode->son->getTailValue();
            return result;
        }
        // 3.1、和后面的节点合并
        if (deleteNextNode != nullptr) {
            IBpTree::TreeNode_merge(tree, treeNode, realDeleteNode, deleteNextNode);
            // 记得此时 deleteNextNode 已经被删除了；别瞎弄了
            realDeleteNode->key = realDeleteNode->son->getTailValue();
            return result;
        }
        // 3.2、和前面的节点合并
        if (deletePreNode != nullptr) {
            IBpTree::TreeNode_merge(tree, treeNode, deletePreNode, realDeleteNode);
            // 记得此时 realDeleteNode 已经被删除了；别瞎弄了
            deletePreNode->key = deletePreNode->son->getTailValue();
            return result;
        }
        throw IException(ERROR_WHEN_DELETE_WHERE_THE_NODE);
    } else if (realDeleteNode->key == key) {
        realDeleteNode->key = realDeleteNode->son->getTailValue();
    }
    return result;
}

BpTreeNode *IBpTree::TreeNode_split(IBpTree *tree, BpTreeNode *treeNode, unsigned int splitLen) {
    if (splitLen < 1 || splitLen > treeNode->cnt) {
        throw IException(ERROR_WHEN_INSERT_PARAM_ERROR_SPLIT);
    }

    NodeItem *splitPosition = treeNode->head;
    for (int step = 0; step < splitLen && splitPosition != nullptr; step++, splitPosition = splitPosition->next);
    assert(splitPosition != nullptr);

    NodeItem *newHead = splitPosition;
    NodeItem *newTail = treeNode->tail;

    treeNode->tail = newHead->pre;
    treeNode->tail->next = nullptr;

    newHead->pre = nullptr;
    auto *newRoot = new BpTreeNode(treeNode->nodeType, newHead, newTail, treeNode->cnt - splitLen);
    treeNode->cnt = splitLen;
    return newRoot;
}

void IBpTree::TreeNode_merge(IBpTree *tree, BpTreeNode *treeNode, NodeIndex *lSon, NodeIndex *rSon) {
    assert(lSon != nullptr);
    assert(rSon != nullptr);

    // 合并数据 => 跳过 rSon
    lSon->next = rSon->next;
    if (rSon->next != nullptr) {
        rSon->next->pre = lSon;
    }

    lSon->son->tail->next = rSon->son->head;
    if (rSon->son->head != nullptr) {
        rSon->son->head->pre = lSon->son->tail;
    }
    lSon->son->tail = rSon->son->tail;
    lSon->son->cnt += rSon->son->cnt;
    // 释放 rSon
    treeNode->cnt--;
    if (treeNode->tail == rSon) {
        treeNode->tail = lSon;
    }
    delete rSon->son;
    delete rSon;
}


