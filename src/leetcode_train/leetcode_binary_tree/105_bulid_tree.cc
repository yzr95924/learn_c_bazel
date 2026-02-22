/**
 * @file 105_bulid_tree.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 105. 从前序与中序遍历序列构造二叉树
 * https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
 * @version 0.1
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

typedef struct TreeNode TreeNode;
static int FindCurRootIdx(int curRootVal, int *inorder, int inorderSize)
{
    int idx = 0;
    for (idx = 0; idx < inorderSize; idx++) {
        if (inorder[idx] == curRootVal) {
            break;
        }
    }
    return idx;
}

static TreeNode *InnerBuildTree(int *preorder, int preorderSize, int *inorder, int inorderSize)
{
    if (preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }
    TreeNode *curRootNode = (TreeNode *)calloc(1, sizeof(TreeNode));
    int curRootVal = preorder[0];
    curRootNode->val = curRootVal;
    int splitIdx = FindCurRootIdx(curRootVal, inorder, inorderSize);
    curRootNode->left = InnerBuildTree(preorder + 1, splitIdx, inorder, splitIdx);
    curRootNode->right = InnerBuildTree(preorder + splitIdx + 1, preorderSize - splitIdx - 1, inorder + splitIdx + 1,
                                        preorderSize - splitIdx - 1);
    return curRootNode;
}

struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize)
{
    return InnerBuildTree(preorder, preorderSize, inorder, inorderSize);
}