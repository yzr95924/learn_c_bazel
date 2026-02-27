/**
 * @file 46_permute.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 46. 全排列 https://leetcode.cn/problems/permutations/description/
 * @version 0.1
 * @date 2026-02-27
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_backtrack.h"

typedef struct {
    int **retAns;
    int *retColSizes;
    size_t ansCnt;
    size_t maxAnsCnt;
} AnsWrapper;

typedef struct {
    int *curAns;
    int curAnsSize;
    bool *isUsed;
} BackTrackState;

static void BackTrack(int *nums, int numsSize, BackTrackState *btState, AnsWrapper *ansWrapper)
{
    if (btState->curAnsSize == numsSize) {
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

    for (int idx = 0; idx < numsSize; idx++) {
        if (btState->isUsed[idx] == true) {
            continue;
        }
        // push
        btState->isUsed[idx] = true;
        btState->curAns[btState->curAnsSize] = nums[idx];
        btState->curAnsSize++;
        BackTrack(nums, numsSize, btState, ansWrapper);
        // pop out
        btState->curAnsSize--;
        btState->isUsed[idx] = false;
    }
    return;
}

int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    AnsWrapper ansWrapper;
    ansWrapper.maxAnsCnt = (size_t)numsSize;
    ansWrapper.ansCnt = 0;
    ansWrapper.retAns = (int **)calloc(ansWrapper.maxAnsCnt, sizeof(int *));
    ansWrapper.retColSizes = (int *)calloc(ansWrapper.maxAnsCnt, sizeof(int));
    BackTrackState btState;
    btState.curAnsSize = 0;
    btState.curAns = (int *)calloc((size_t)numsSize, sizeof(int));
    btState.isUsed = (bool *)calloc((size_t)numsSize, sizeof(bool));

    BackTrack(nums, numsSize, &btState, &ansWrapper);

    *returnSize = (int)ansWrapper.ansCnt;
    *returnColumnSizes = ansWrapper.retColSizes;
    free(btState.curAns);
    return ansWrapper.retAns;
}