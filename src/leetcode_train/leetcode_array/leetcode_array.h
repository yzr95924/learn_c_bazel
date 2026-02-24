/**
 * @file leetcode_binary_tree.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief leetcode array question header
 * @version 0.1
 * @date 2026-02-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LEETCODE_ARRAY
#define LEETCODE_ARRAY

#include "common_util.h"

// 27. 移除元素
// https://leetcode.cn/problems/remove-element/description/
int removeElement(int *nums, int numsSize, int val);

// 33. 搜索旋转排序数组
// https://leetcode.cn/problems/search-in-rotated-sorted-array/description/
int search_33(int *nums, int numsSize, int target);

// 34. 在排序数组中查找元素的第一个和最后一个位置
// https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/description/
int *searchRange(int *nums, int numsSize, int target, int *returnSize);

// 53. 最大子数组和
// https://leetcode.cn/problems/maximum-subarray/description/
int maxSubArray(int *nums, int numsSize);

// 287. 寻找重复数
// https://leetcode.cn/problems/find-the-duplicate-number/description/
int findDuplicate(int *nums, int numsSize);

// 704. 二分查找
// https://leetcode.cn/problems/binary-search/description/
int search(int *nums, int numsSize, int target);

#endif