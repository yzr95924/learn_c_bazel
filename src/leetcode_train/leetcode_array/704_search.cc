/**
 * @file 704_search.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 704. 二分查找 https://leetcode.cn/problems/binary-search/description/
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_array.h"

// 红绿灯法
static int InnerBinSearch(int *arr, int numsSize, int target)
{
    int left = -1;
    int right = numsSize;
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > target) {
            right = mid;
        } else if (arr[mid] < target) {
            left = mid;
        } else {
            return mid;
        }
    }
    return -1;
}

int search(int *nums, int numsSize, int target) { return InnerBinSearch(nums, numsSize, target); }