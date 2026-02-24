/**
 * @file 152_max_product.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 152. 乘积最大子数组 https://leetcode.cn/problems/maximum-product-subarray/description/
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

static int FindMin(int a, int b, int c)
{
    int min = a < b ? a : b;
    min = min > c ? c : min;
    return min;
}

static int FindMax(int a, int b, int c)
{
    int max = a > b ? a : b;
    max = max > c ? max : c;
    return max;
}

int maxProduct(int *nums, int numsSize)
{
    int *dpMax = (int *)calloc((size_t)numsSize, sizeof(int));
    int *dpMin = (int *)calloc((size_t)numsSize, sizeof(int));
    dpMax[0] = nums[0];
    dpMin[0] = nums[0];

    for (int idx = 1; idx < numsSize; idx++) {
        dpMax[idx] = FindMax(dpMax[idx - 1] * nums[idx], dpMin[idx - 1] * nums[idx], nums[idx]);
        dpMin[idx] = FindMin(dpMax[idx - 1] * nums[idx], dpMin[idx - 1] * nums[idx], nums[idx]);
    }
    int ans = FindMaxItem(dpMax, numsSize);
    free(dpMax);
    free(dpMin);
    return ans;
}