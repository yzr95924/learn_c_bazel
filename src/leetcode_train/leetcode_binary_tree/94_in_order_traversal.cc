/**
 * @file 94_in_order_traversal.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 94. 二叉树的中序遍历 https://leetcode.cn/problems/binary-tree-inorder-traversal/description/
 * @version 0.1
 * @date 2026-02-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

typedef struct TreeNode TreeNode;
static const int kMaxTreeNodeCnt = 100;

static void InnerInorderTraversal(TreeNode *root, int *retArr, int *retNum)
{
    if (root == NULL) {
        return;
    }
    InnerInorderTraversal(root->left, retArr, retNum);
    retArr[*retNum] = root->val;
    (*retNum)++;
    InnerInorderTraversal(root->right, retArr, retNum);
    return;
}

int *inorderTraversal(struct TreeNode *root, int *returnSize)
{
    int *retArr = (int *)calloc(kMaxTreeNodeCnt, sizeof(int));
    int retNum = 0;
    InnerInorderTraversal(root, retArr, &retNum);
    *returnSize = retNum;
    return retArr;
}