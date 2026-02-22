/**
 * @file 114_flatten.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 114. 二叉树展开为链表 https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/description/
 * @version 0.1
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

typedef struct TreeNode TreeNode;

static const int kMaxNodeNum = 2000;

static void InnerFirstTraverse(TreeNode *curNode, TreeNode **nodePtrArr, int *nodeCnt)
{
    if (curNode == NULL) {
        return;
    }
    (nodePtrArr)[*nodeCnt] = curNode;
    (*nodeCnt)++;
    InnerFirstTraverse(curNode->left, nodePtrArr, nodeCnt);
    InnerFirstTraverse(curNode->right, nodePtrArr, nodeCnt);
    return;
}

void flatten(struct TreeNode *root)
{
    TreeNode **nodePtrArr = (TreeNode **)calloc(kMaxNodeNum, sizeof(TreeNode *));
    int nodeCnt = 0;
    InnerFirstTraverse(root, nodePtrArr, &nodeCnt);
    for (int idx = 0; idx < nodeCnt - 1; idx++) {
        nodePtrArr[idx]->right = nodePtrArr[idx + 1];
        nodePtrArr[idx]->left = NULL;
    }
    return;
}