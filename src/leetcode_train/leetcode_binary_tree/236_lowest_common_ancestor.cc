/**
 * @file 236_lowest_common_ancestor.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 236. 二叉树的最近公共祖先 https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/
 * @version 0.1
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

typedef struct TreeNode TreeNode;

static TreeNode *g_ans = NULL;

static bool CheckHasValue(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == NULL) {
        return false;
    }
    bool isLeftTreeFind = CheckHasValue(root->left, p, q);
    bool isRightTreeFind = CheckHasValue(root->right, p, q);
    if ((isLeftTreeFind && isRightTreeFind) ||
        (((root->val == p->val) || (root->val == q->val)) && (isLeftTreeFind || isRightTreeFind))) {
        g_ans = root;
    }
    return isLeftTreeFind || isRightTreeFind || root->val == p->val || root->val == q->val;
}

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q)
{
    if (CheckHasValue(root, p, q)) {
        return g_ans;
    }
    return NULL;
}