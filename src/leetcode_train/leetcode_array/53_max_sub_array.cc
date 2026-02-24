/**
 * @file 53_max_sub_array.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 53. 最大子数组和 https://leetcode.cn/problems/maximum-subarray/description/
 * @version 0.1
 * @date 2026-02-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_array.h"

static int FindMaxItem(int *nums, int numsSize)
{
    int max = INT_MIN;
    for (int idx = 0; idx < numsSize; idx++) {
        if (nums[idx] > max) {
            max = nums[idx];
        }
    }
    return max;
}

int maxSubArray(int *nums, int numsSize)
{
    if (numsSize == 1) {
        return nums[0];
    }
    int *dp = (int *)calloc((size_t)numsSize, sizeof(int));
    dp[0] = nums[0];
    for (int idx = 1; idx < numsSize; idx++) {
        int tmpSum = dp[idx - 1] + nums[idx];
        if (tmpSum > nums[idx]) {
            dp[idx] = tmpSum;
        } else {
            dp[idx] = nums[idx];
        }
    }
    int ans = FindMaxItem(dp, numsSize);
    free(dp);
    return ans;
}