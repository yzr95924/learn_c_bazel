/**
 * @file 39_combination_sum.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 39. 组合总和 https://leetcode.cn/problems/combination-sum/description/
 * @version 0.1
 * @date 2026-02-27
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_backtrack.h"

static int CmpAscend(const void *a, const void *b)
{
    int latter = *(const int *)a;
    int former = *(const int *)b;
    return latter - former;
}

typedef struct {
    int **retAns;
    int *retColSizes;
    size_t ansCnt;
    size_t maxAnsCnt;
} AnsWrapper;

typedef struct {
    int *curAns;
    int curAnsSize;
} BackTrackState;

static void BackTrack(int *candidate, int candidatesSize, BackTrackState *btState,
                      AnsWrapper *ansWrapper, int target, int startIdx)
{
    int curSum = 0;
    for (int idx = 0; idx < btState->curAnsSize; idx++) {
        curSum += btState->curAns[idx];
    }
    if (curSum > target) {
        return;
    }
    if (curSum == target) {
        ansWrapper->retAns[ansWrapper->ansCnt] =
            (int *)calloc((size_t)btState->curAnsSize, sizeof(int));
        ansWrapper->retColSizes[ansWrapper->ansCnt] = btState->curAnsSize;
        memcpy(ansWrapper->retAns[ansWrapper->ansCnt], btState->curAns,
               (size_t)btState->curAnsSize * sizeof(int));
        ansWrapper->ansCnt++;

        if (ansWrapper->ansCnt == ansWrapper->maxAnsCnt) {
            ansWrapper->maxAnsCnt = ansWrapper->maxAnsCnt * 2;
            ansWrapper->retAns =
                (int **)realloc(ansWrapper->retAns, ansWrapper->maxAnsCnt * sizeof(int *));
            ansWrapper->retColSizes =
                (int *)realloc(ansWrapper->retColSizes, ansWrapper->maxAnsCnt * sizeof(int));
        }
    }

    for (int idx = startIdx; idx < candidatesSize; idx++) {
        // push
        btState->curAns[btState->curAnsSize] = candidate[idx];
        btState->curAnsSize++;
        BackTrack(candidate, candidatesSize, btState, ansWrapper, target, idx);
        // pop out
        btState->curAnsSize--;
    }
    return;
}

int **combinationSum(int *candidates, int candidatesSize, int target, int *returnSize,
                     int **returnColumnSizes)
{
    qsort(candidates, (size_t)candidatesSize, sizeof(int), CmpAscend);
    AnsWrapper ansWrapper;
    ansWrapper.maxAnsCnt = (size_t)candidatesSize;
    ansWrapper.ansCnt = 0;
    ansWrapper.retAns = (int **)calloc(ansWrapper.maxAnsCnt, sizeof(int *));
    ansWrapper.retColSizes = (int *)calloc(ansWrapper.maxAnsCnt, sizeof(int));
    BackTrackState btState;
    btState.curAnsSize = 0;
    btState.curAns = (int *)calloc((size_t)candidatesSize * 100, sizeof(int));

    BackTrack(candidates, candidatesSize, &btState, &ansWrapper, target, 0);

    *returnSize = (int)ansWrapper.ansCnt;
    *returnColumnSizes = ansWrapper.retColSizes;
    free(btState.curAns);
    return ansWrapper.retAns;
}