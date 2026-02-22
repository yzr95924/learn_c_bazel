/**
 * @file 98_is_valid_bst.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 98. 验证二叉搜索树 https://leetcode.cn/problems/validate-binary-search-tree/description/
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

typedef struct TreeNode TreeNode;

static bool CheckIsValidBST(TreeNode *root, int64_t lowBound, int64_t upBound)
{
    if (root == NULL) {
        return true;
    }
    if ((int64_t)root->val <= lowBound || (int64_t)root->val >= upBound) {
        return false;
    }
    return (CheckIsValidBST(root->left, lowBound, root->val) && CheckIsValidBST(root->right, root->val, upBound));
}

bool isValidBST(struct TreeNode *root) { return CheckIsValidBST(root, INT64_MIN, INT64_MAX); }