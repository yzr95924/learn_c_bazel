/**
 * @file 77_combine.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 77. 组合 https://leetcode.cn/problems/combinations/description/
 * @version 0.1
 * @date 2026-02-26
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_backtrack.h"

static size_t GetFactorial(size_t inputVal)
{
    size_t retVal = 1;
    for (size_t i = inputVal; i > 0; i--) {
        retVal *= i;
    }
    return retVal;
}

typedef struct {
    int **retAns;
    int cnt;
} AnsWrapper;

typedef struct {
    int *curAns;
    int curSize;
} BackTrackState;

static void BackTrack(AnsWrapper *ansWrapper, BackTrackState *btState, int n, int k, int startIdx)
{
    if (btState->curSize == k) {
        memcpy(ansWrapper->retAns[ansWrapper->cnt], btState->curAns, sizeof(int) * (size_t)k);
        ansWrapper->cnt++;
        return;
    }

    for (int idx = startIdx; idx <= n; idx++) {
        // do op
        btState->curAns[btState->curSize] = idx;
        btState->curSize++;
        BackTrack(ansWrapper, btState, n, k, idx + 1);

        // revert op
        btState->curSize--;
    }
    return;
}

int **combine(int n, int k, int *returnSize, int **returnColumnSizes)
{
    // 全排列个数计算公式
    size_t returnAnsNum = GetFactorial((size_t)n) / (GetFactorial((size_t)k) * GetFactorial((size_t)(n - k)));
    AnsWrapper ansWrapper;
    ansWrapper.retAns = (int **)calloc(returnAnsNum, sizeof(int *));
    ansWrapper.cnt = 0;
    for (size_t idx = 0; idx < returnAnsNum; idx++) {
        ansWrapper.retAns[idx] = (int *)calloc((size_t)k, sizeof(int));
    }

    *returnColumnSizes = (int *)calloc(returnAnsNum, sizeof(int));
    for (size_t idx = 0; idx < returnAnsNum; idx++) {
        (*returnColumnSizes)[idx] = k;
    }

    BackTrackState btState;
    btState.curSize = 0;
    btState.curAns = (int *)calloc((size_t)k, sizeof(int));

    BackTrack(&ansWrapper, &btState, n, k, 1);

    free(btState.curAns);
    *returnSize = (int)returnAnsNum;
    return ansWrapper.retAns;
}