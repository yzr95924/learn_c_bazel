/**
 * @file 101_is_symmetric.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 101. 对称二叉树 https://leetcode.cn/problems/symmetric-tree/description/
 * @version 0.1
 * @date 2026-02-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

typedef struct TreeNode TreeNode;

static bool CheckIsSymmetric(TreeNode *leftPtr, TreeNode *rightPtr)
{
    if (leftPtr == NULL && rightPtr == NULL) {
        return true;
    }
    if ((leftPtr != NULL && rightPtr == NULL) || (leftPtr == NULL && rightPtr != NULL)) {
        return false;
    }
    return ((leftPtr->val == rightPtr->val) && CheckIsSymmetric(leftPtr->left, rightPtr->right) &&
            CheckIsSymmetric(leftPtr->right, rightPtr->left));
}

bool isSymmetric(struct TreeNode *root) { return CheckIsSymmetric(root->left, root->right); }