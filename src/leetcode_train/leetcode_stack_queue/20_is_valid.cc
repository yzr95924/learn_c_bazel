/**
 * @file 20_is_valid.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 20. 有效的括号 https://leetcode.cn/problems/valid-parentheses/description/
 * @version 0.1
 * @date 2026-02-26
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_stack_queue.h"

#define EMPTY_STACK_TOP_IDX (-1)

static bool IsLeftChar(char inputChar)
{
    switch (inputChar) {
        case '(':
        case '{':
        case '[':
            return true;
        default:
            break;
    }
    return false;
}

static bool IsRightChar(char inputChar)
{
    switch (inputChar) {
        case ')':
        case '}':
        case ']':
            return true;
        default:
            break;
    }
    return false;
}

static bool CheckPair(char inputChar, char oriChar)
{
    switch (inputChar) {
        case ')':
            if (oriChar == '(') {
                return true;
            }
            break;
        case '}':
            if (oriChar == '{') {
                return true;
            }
            break;
        case ']':
            if (oriChar == '[') {
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

bool isValid(char *s)
{
    size_t inputStrLen = strlen(s);
    char *stack = (char *)calloc(inputStrLen, sizeof(char));
    int topIdx = EMPTY_STACK_TOP_IDX;

    bool ans = true;
    for (size_t idx = 0; idx < inputStrLen; idx++) {
        if (IsLeftChar(s[idx])) {
            // push
            topIdx++;
            stack[topIdx] = s[idx];
        }
        if (IsRightChar(s[idx])) {
            if (topIdx != EMPTY_STACK_TOP_IDX && CheckPair(s[idx], stack[topIdx])) {
                // pair success
                topIdx--;
            } else {
                ans = false;
                break;
            }
        }
    }
    if (topIdx != EMPTY_STACK_TOP_IDX) {
        ans = false;
    }

    return ans;
}