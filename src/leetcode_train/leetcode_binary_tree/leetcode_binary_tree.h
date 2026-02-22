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

// 101. 对称二叉树
// https://leetcode.cn/problems/symmetric-tree/description/
bool isSymmetric(struct TreeNode *root);

// 102. 二叉树的层序遍历
// https://leetcode.cn/problems/binary-tree-level-order-traversal/description/
int **levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes);

// 104. 二叉树的最大深度
// https://leetcode.cn/problems/maximum-depth-of-binary-tree/description/
int maxDepth(struct TreeNode *root);

// 105. 从前序与中序遍历序列构造二叉树
// https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize);

// 114. 二叉树展开为链表
// https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/description/
void flatten(struct TreeNode *root);

// 226. 翻转二叉树
// https://leetcode.cn/problems/invert-binary-tree/description/
struct TreeNode *invertTree(struct TreeNode *root);

#endif