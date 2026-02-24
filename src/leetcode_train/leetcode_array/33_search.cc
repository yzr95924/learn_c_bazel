/**
 * @file 33_search.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 33. 搜索旋转排序数组 https://leetcode.cn/problems/search-in-rotated-sorted-array/description/
 * @version 0.1
 * @date 2026-02-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_array.h"

static int FindMinIdx(int *nums, int numsSize)
{
    int left = -1;
    int right = numsSize - 1; // 注意要刨去最后一个元素，所有哨兵idx为numsSize - 1;
    // 绿区定义：未发现旋转点的
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < nums[numsSize - 1]) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return right;
}

static int FindExistTarget(int *nums, int numsSize, int target)
{
    int left = -1;
    int right = numsSize;
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid;
        } else if (nums[mid] > target) {
            right = mid;
        } else {
            return mid;
        }
    }
    return -1;
}

int search_33(int *nums, int numsSize, int target)
{
    int minValIdx = FindMinIdx(nums, numsSize);
    int leftSegLen = minValIdx;
    int rightSegLen = numsSize - minValIdx;

    int leftSegFindRet = FindExistTarget(nums, leftSegLen, target);
    if (leftSegFindRet != -1) {
        return leftSegFindRet;
    }

    int rightSegFindRet = FindExistTarget(&nums[leftSegLen], rightSegLen, target);
    if (rightSegFindRet != -1) {
        return (leftSegLen + rightSegFindRet);
    }

    return -1;
}
