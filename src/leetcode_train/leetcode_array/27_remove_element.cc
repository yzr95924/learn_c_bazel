/**
 * @file 27_remove_element.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 27. 移除元素 https://leetcode.cn/problems/remove-element/description/
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_array.h"

int removeElement(int *nums, int numsSize, int val)
{
    int leftIdx = 0;
    for (int rightIdx = 0; rightIdx < numsSize; rightIdx++) {
        if (nums[rightIdx] != val) {
            nums[leftIdx] = nums[rightIdx];
            leftIdx++;
        }
    }
    return leftIdx;
}