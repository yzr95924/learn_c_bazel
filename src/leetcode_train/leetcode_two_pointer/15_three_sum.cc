/**
 * @file 15_three_sum.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 15. 三数之和 https://leetcode.cn/problems/3sum/description/
 * @version 0.1
 * @date 2026-02-26
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_two_pointer.h"

int CmpAscend(const void *a, const void *b)
{
    int latter = *(const int *)a;
    int former = *(const int *)b;
    return latter - former;
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    int maxAnsNum = numsSize;
    int curAnsNum = 0;
    int **retAns = (int **)calloc((size_t)maxAnsNum, sizeof(int *));
    *returnColumnSizes = (int *)calloc((size_t)maxAnsNum, sizeof(int));

    // 升序排序
    qsort(nums, (size_t)numsSize, sizeof(int), CmpAscend);

    int leftIdx = 0;
    int rightIdx = 0;
    for (int startIdx = 0; startIdx < numsSize - 2; startIdx++) {
        if (nums[startIdx] > 0) {
            continue;
        }

        if (startIdx > 0 && nums[startIdx] == nums[startIdx - 1]) {
            continue;
        }

        leftIdx = startIdx + 1;
        rightIdx = numsSize - 1;
        while (rightIdx - leftIdx >= 1) {
            int curSum = nums[startIdx] + nums[leftIdx] + nums[rightIdx];
            if (curSum > 0) {
                rightIdx--;
            } else if (curSum < 0) {
                leftIdx++;
            } else {
                retAns[curAnsNum] = (int *)calloc(3, sizeof(int));
                (*returnColumnSizes)[curAnsNum] = 3;
                retAns[curAnsNum][0] = nums[startIdx];
                retAns[curAnsNum][1] = nums[leftIdx];
                retAns[curAnsNum][2] = nums[rightIdx];
                curAnsNum++;

                if (curAnsNum == maxAnsNum) {
                    maxAnsNum *= 2;
                    retAns = (int **)realloc(retAns, sizeof(int *) * (size_t)maxAnsNum);
                    *returnColumnSizes = (int *)realloc((*returnColumnSizes), sizeof(int) * (size_t)maxAnsNum);
                }

                // 去重
                while (rightIdx > leftIdx && nums[rightIdx] == nums[rightIdx - 1]) rightIdx--;
                while (rightIdx > leftIdx && nums[leftIdx] == nums[leftIdx + 1]) leftIdx++;

                rightIdx--;
                leftIdx++;
            }
        }
    }
    *returnSize = curAnsNum;
    return retAns;
}