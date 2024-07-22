//
// Created by libao02 on 2022/7/29.
//

#include "../header/IBpTree.h"
#include <string>
#include <iostream>

IBpTree::IBpTree(int mm) {
    this->root = nullptr;
    this->nodeMaxItemCnt = mm;
    this->nodeMinItemCnt = (mm >> 1u);
    this->dataCount = 0;
    this->high = 0;
}

void IBpTree::put(int key) {
    // case1 ： 第一个元素
    if (this->root == nullptr) {
        this->root = new BpTreeNode(key, Data);
        return;
    }
    BpTreeNode *bePopData = IBpTree::Node_put(this, this->root, key);
    // 跟节点收到 pop 意味着 树的生长
    if (bePopData != nullptr) {
        this->high++;
        auto *newRoot = new BpTreeNode(Index, nullptr, nullptr, 0);
        BpTreeNode::insertAfterTailNode(newRoot, new NodeIndex(this->root));
        BpTreeNode::insertAfterTailNode(newRoot, new NodeIndex(bePopData));
        this->root = newRoot;
    }
}

void IBpTree::remove(int id) {
    if (this->root == nullptr) {
        return;
    }
    IBpTree::Node_remove(this, this->root, id);
}


int IBpTree::contain(int id) {
    throw "TODO";
}

void IBpTree::toString() {
    std::cout << "Deep:=" << this->high << ";" << "Cnt:=" << this->dataCount << std::endl;
    std::cout << this->Func_toString(this->root, this->high, "") << std::endl;
}

std::string IBpTree::Func_toString(BpTreeNode *findNode, unsigned int findNodeHigh, const std::string &indent) {
    std::string s = "";
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
            s += this->Func_toString(((NodeIndex *) flag)->son, findNodeHigh - 1, indent + "     ");
            flag = flag->pre;
        }
    }
    return s;
}

BpTreeNode *IBpTree::Node_put(IBpTree *tree, BpTreeNode *root, int key) {
    // 索引结点
    NodeItem *insertPosition = root->head;
    // 找到 需要插入的 游标地址
    while (insertPosition->next != nullptr) {
        if (key <= insertPosition->key) {
            break;
        }
        insertPosition = insertPosition->next;
    }
    if (root->getNodeType() == Data) {
        // 数据插入 => 数据结点
        NodeItem *inLink = new NodeData(key);
        // 向前插入
        if (key < insertPosition->key) {
            BpTreeNode::insertBeforeNode(root, insertPosition, inLink);
        } else if (key > insertPosition->key) {
            BpTreeNode::insertAfterNode(root, insertPosition, inLink);
        } else {
            // 不允许重复
            return nullptr;
        }
        root->cnt++;
    } else {
        // 数据插入 => 索引结点
        auto *indexFlag = (NodeIndex *) insertPosition;
        BpTreeNode *flagSon = indexFlag->son;
        if (flagSon == nullptr) {
            throw "不可能，索引节点一定有儿子节点";
        }

        BpTreeNode *poped = IBpTree::Node_put(tree, flagSon, key);
        // 儿子分裂 pop 上来的元素
        if (poped != nullptr) {
            NodeItem *inLink = new NodeIndex(poped);
            BpTreeNode::insertAfterNode(root, insertPosition, inLink);
            root->cnt++;
        }
        // 更正索引的值
        insertPosition->key = flagSon->getTailValue();
    }
    // 分裂成两个并且 给 到父亲节点。
    if (root->cnt > tree->nodeMaxItemCnt) {
        return IBpTree::Node_split(tree, root, tree->nodeMinItemCnt);
    }
    return nullptr;
}

int IBpTree::Node_remove(IBpTree *tree, BpTreeNode *treeNode, int key) {
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
            BpTreeNode::deleteNode(treeNode, deletePosition);
        } else {
            return 0;
        }
    } else {
        auto *indexFlag = (NodeIndex *) deletePosition;
        BpTreeNode *flagSon = indexFlag->son;
        IBpTree::Node_remove(tree, flagSon, key);
        // 需要匀一匀数据；
        if (flagSon->cnt < tree->nodeMaxItemCnt) {
            // TODO
            // 1、看前后那个结点可以匀数据出来；如果前后都不够 则和前面的结点合并;
        }
    }
}

BpTreeNode *IBpTree::Node_split(IBpTree *tree, BpTreeNode *treeNode, unsigned int splitLen) {
    if (splitLen < 1 || splitLen > treeNode->cnt) {
        throw "分裂长度不对";
    }

    NodeItem *splitPosition = treeNode->head;
    for (int step = 0; step < splitLen && splitPosition != nullptr; step++, splitPosition = splitPosition->next);
    assert(splitPosition != nullptr);

    NodeItem *newHead = splitPosition;
    NodeItem *newTail = treeNode->tail;

    treeNode->tail = newHead->pre;

    newHead->pre->next = nullptr;
    newHead->pre = nullptr;
    auto *newRoot = new BpTreeNode(treeNode->nodeType, newHead, newTail, treeNode->cnt - splitLen);
    treeNode->cnt = splitLen;
    return newRoot;
}


