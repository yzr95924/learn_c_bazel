/**
 * @file 287_find_duplicate.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 287. 寻找重复数 https://leetcode.cn/problems/find-the-duplicate-number/description/
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_array.h"

// 基于红绿灯模板写的，红区是满足的，绿区是多的
int findDuplicate(int *nums, int numsSize)
{
    int left = 0;
    int right = numsSize + 1;
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        int count = 0;
        for (int idx = 0; idx < numsSize; idx++) {
            if (nums[idx] <= mid) {
                count++;
            }
        }
        if (count > mid) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return right;
}