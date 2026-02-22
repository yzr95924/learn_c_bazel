/**
 * @file 617_merge_trees.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 617. 合并二叉树 https://leetcode.cn/problems/merge-two-binary-trees/description/
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

typedef struct TreeNode TreeNode;

static TreeNode *InnerMergeTree(TreeNode *root1, TreeNode *root2)
{
    if (root1 == NULL) {
        return root2;
    }
    if (root2 == NULL) {
        return root1;
    }
    TreeNode *curRoot = (TreeNode *)calloc(1, sizeof(TreeNode));
    curRoot->val = root1->val + root2->val;
    curRoot->left = InnerMergeTree(root1->left, root2->left);
    curRoot->right = InnerMergeTree(root1->right, root2->right);
    return curRoot;
}

struct TreeNode *mergeTrees(struct TreeNode *root1, struct TreeNode *root2) { return InnerMergeTree(root1, root2); }