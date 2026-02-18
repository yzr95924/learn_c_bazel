/**
 * @file 226_invert_tree.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 226. 翻转二叉树 https://leetcode.cn/problems/invert-binary-tree/description/
 * @version 0.1
 * @date 2026-02-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

typedef struct TreeNode TreeNode;

static void InnerInvertTree(TreeNode *curNode)
{
    if (curNode == NULL) {
        return;
    }
    TreeNode *tmpTreeNode = curNode->left;
    curNode->left = curNode->right;
    curNode->right = tmpTreeNode;
    InnerInvertTree(curNode->left);
    InnerInvertTree(curNode->right);
    return;
}

struct TreeNode *invertTree(struct TreeNode *root)
{
    InnerInvertTree(root);
    return root;
}