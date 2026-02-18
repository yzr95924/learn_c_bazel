/**
 * @file 102_level_order.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 102. 二叉树的层序遍历 https://leetcode.cn/problems/binary-tree-level-order-traversal/description/
 * @version 0.1
 * @date 2026-02-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

typedef struct TreeNode TreeNode;
static const size_t kMaxTreeNodeNum = 2000;

static int GetTreeDepth(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    return (int)fmax((double)GetTreeDepth(root->left), (double)GetTreeDepth(root->right)) + 1;
}

static void InnerLevelOrder(TreeNode *curTreeNode, int **retArr, int depth, int **returnColumnSizes)
{
    if (curTreeNode == NULL) {
        return;
    }
    int curIdx = (*returnColumnSizes)[depth];
    retArr[depth][curIdx] = curTreeNode->val;
    (*returnColumnSizes)[depth] = curIdx + 1;
    InnerLevelOrder(curTreeNode->left, retArr, depth + 1, returnColumnSizes);
    InnerLevelOrder(curTreeNode->right, retArr, depth + 1, returnColumnSizes);
    return;
}

int **levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
{
    int treeDepth = GetTreeDepth(root);
    int **retArr = (int **)calloc((size_t)treeDepth, sizeof(int *));
    for (int idx = 0; idx < treeDepth; idx++) {
        retArr[idx] = (int *)calloc(kMaxTreeNodeNum, sizeof(int));
    }
    *returnSize = treeDepth;
    *returnColumnSizes = (int *)calloc((size_t)treeDepth, sizeof(int));
    InnerLevelOrder(root, retArr, 0, returnColumnSizes);
    return retArr;
}