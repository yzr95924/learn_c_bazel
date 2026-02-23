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

int findDuplicate(int *nums, int numsSize)
{
    int left = 1;
    int right = numsSize - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int count = 0;
        for (int idx = 0; idx < numsSize; idx++) {
            if (nums[idx] <= mid) {
                count++;
            }
        }
        if (mid < count) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}