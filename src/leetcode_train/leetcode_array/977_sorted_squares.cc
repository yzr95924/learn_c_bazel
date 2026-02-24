/**
 * @file 977_sorted_squares.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 977. 有序数组的平方 https://leetcode.cn/problems/squares-of-a-sorted-array/description/
 * @version 0.1
 * @date 2026-02-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_array.h"

int *sortedSquares(int *nums, int numsSize, int *returnSize)
{
    int leftIdx = 0;
    int rightIdx = numsSize - 1;

    int *retArr = (int *)calloc((size_t)numsSize, sizeof(int));
    *returnSize = numsSize;
    if (numsSize == 1) {
        retArr[0] = nums[0] * nums[0];
        return retArr;
    }

    int retIdx = numsSize - 1;
    while (leftIdx <= rightIdx) {
        int rightSquare = nums[rightIdx] * nums[rightIdx];
        int leftSquare = nums[leftIdx] * nums[leftIdx];
        if (rightSquare > leftSquare) {
            retArr[retIdx] = rightSquare;
            rightIdx--;
        } else {
            retArr[retIdx] = leftSquare;
            leftIdx++;
        }
        retIdx--;
    }
    return retArr;
}