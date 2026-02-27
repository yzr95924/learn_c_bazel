/**
 * @file 40_combination_sum_2.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 40. 组合总和 II https://leetcode.cn/problems/combination-sum-ii/description/
 * @version 0.1
 * @date 2026-02-27
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_backtrack.h"

typedef struct {
    int **retAns;
    int cnt;
} ANsWrapper;

typedef struct {
    int *curAns;
    int curSize;
    bool *isUsedArr;
} BackTrackState;

// static void BackTrack(ANsWrapper *ansWrapper, BackTrackState *btState, int target, int *maxAns)
// {
//     int curSum = 0;
//     for (int idx = 0; idx < btState->curSize; idx++) {
//         curSum += btState->curAns[idx];
//     }
//     if (curSum == target) {
//         ansWrapper->retAns[ansWrapper->cnt] =
//     }

//     return;
// }

int **combinationSum2(int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes)
{
    // int maxAns = candidatesSize;
    // bool *isUsedArr = (bool *)calloc(candidatesSize, sizeof(bool)); // default to false

    UNUSED_PARAM(candidates);
    UNUSED_PARAM(candidatesSize);
    UNUSED_PARAM(target);
    UNUSED_PARAM(returnSize);
    UNUSED_PARAM(returnColumnSizes);
    return NULL;
}
