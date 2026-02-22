/**
 * @file 96_num_trees.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 96. 不同的二叉搜索树 https://leetcode.cn/problems/unique-binary-search-trees/description/
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_binary_tree.h"

int numTrees(int n)
{
    int *numTreesArr = (int *)calloc((size_t)n + 1, sizeof(int));
    numTreesArr[0] = 1;
    numTreesArr[1] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            numTreesArr[i] += numTreesArr[j - 1] * numTreesArr[i - j];
        }
    }
    int ans = numTreesArr[n];
    free(numTreesArr);
    return ans;
}