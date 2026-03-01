/**
 * @file 621_least_interval.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 621. 任务调度器 https://leetcode.cn/problems/task-scheduler/description/
 * @version 0.1
 * @date 2026-03-02
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_app.h"

static const int kTaskNum = 26;

int leastInterval(char *tasks, int tasksSize, int n)
{
    UNUSED_PARAM(n);
    int freq[kTaskNum] = {0};
    // count the task freq
    for (int idx = 0; idx < tasksSize; idx++) {
        freq[tasks[idx] - 'A']++;
    }

    // 维护nextValid数组、剩余执行任务次数数组
    int time = 0;
    for (int idx = 0; idx < tasksSize; idx++) {
        time++;
    }

    return time;
}