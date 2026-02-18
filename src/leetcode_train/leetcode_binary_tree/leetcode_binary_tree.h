/**
 * @file leetcode_binary_tree.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief leetcode binary tree question header
 * @version 0.1
 * @date 2026-02-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LEETCODE_BINARY_TREE
#define LEETCODE_BINARY_TREE

#include "common_util.h"
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 94. 二叉树的中序遍历
// https://leetcode.cn/problems/binary-tree-inorder-traversal/description/
int *inorderTraversal(struct TreeNode *root, int *returnSize);

#endif