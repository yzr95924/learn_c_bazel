/**
 * @file 104_max_depth.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 104. 二叉树的最大深度 https://leetcode.cn/problems/maximum-depth-of-binary-tree/description/
 * @version 0.1
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

typedef struct TreeNode TreeNode;

static int GetMaxDepth(TreeNode *curNode)
{
    if (curNode == NULL) {
        return 0;
    }
    return (int)fmax((double)GetMaxDepth(curNode->left), (double)GetMaxDepth(curNode->right)) + 1;
}

int maxDepth(struct TreeNode *root) { return GetMaxDepth(root); }