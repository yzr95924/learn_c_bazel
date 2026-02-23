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

// 287. 寻找重复数
// https://leetcode.cn/problems/find-the-duplicate-number/description/
int findDuplicate(int *nums, int numsSize);

// 704. 二分查找
// https://leetcode.cn/problems/binary-search/description/
int search(int *nums, int numsSize, int target);

#endif