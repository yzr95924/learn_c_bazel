/**
 * @file 34_search_range.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 34. 在排序数组中查找元素的第一个和最后一个位置
 * https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/description/
 * @version 0.1
 * @date 2026-02-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_array.h"

static int FindFirstHighIdx(int *nums, int numsSize, int target)
{
    int left = -1;
    int right = numsSize;
    // green area: > target
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > target) {
            // green area: > target
            right = mid;
        } else {
            // red area: <= target
            left = mid;
        }
    }
    return right - 1;
}

static int FindLatestLowIdx(int *nums, int numsSize, int target)
{
    int left = -1;
    int right = numsSize;
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            // red area: < target
            left = mid;
        } else {
            // green area: >= target
            right = mid;
        }
    }
    if (nums[right] != target) {
        return -1;
    }
    return left + 1;
}

static int FindBinSearch(int *nums, int numsSize, int target)
{
    int left = -1;
    int right = numsSize;
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > target) {
            // green area: > target
            right = mid;
        } else if (nums[mid] < target) {
            // red area: < target
            left = mid;
        } else {
            return mid;
        }
    }
    return -1;
}

int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
    *returnSize = 2;
    int *retArr = (int *)calloc(2, sizeof(int));
    if (FindBinSearch(nums, numsSize, target) == -1) {
        retArr[0] = -1;
        retArr[1] = -1;
    } else {
        retArr[0] = FindLatestLowIdx(nums, numsSize, target);
        retArr[1] = FindFirstHighIdx(nums, numsSize, target);
    }
    return retArr;
}