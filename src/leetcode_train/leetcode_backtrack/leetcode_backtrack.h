/**
 * @file leetcode_backtrack.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief leetcode backtracking question header
 * @version 0.1
 * @date 2026-02-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LEETCODE_BACK_TRACK
#define LEETCODE_BACK_TRACK

#include "common_util.h"

// 39. 组合总和
// https://leetcode.cn/problems/combination-sum/description/
int **combinationSum(int *candidates, int candidatesSize, int target, int *returnSize,
                     int **returnColumnSizes);

// 40. 组合总和 II
// https://leetcode.cn/problems/combination-sum-ii/description/
int **combinationSum2(int *candidates, int candidatesSize, int target, int *returnSize,
                      int **returnColumnSizes);

// 46. 全排列
// https://leetcode.cn/problems/permutations/description/
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes);

// 77. 组合
// https://leetcode.cn/problems/combinations/description/
int **combine(int n, int k, int *returnSize, int **returnColumnSizes);

#endif