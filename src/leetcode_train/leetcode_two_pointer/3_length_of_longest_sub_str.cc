/**
 * @file 3_length_of_longest_sub_str.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 3. 无重复字符的最长子串
 * https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/
 * @version 0.1
 * @date 2026-02-27
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_two_pointer.h"

static bool IsCurWindowsDup(uint8_t *bitMap, char *subStr, int len)
{
    for (int idx = 0; idx < len; idx++) {
        int pos = (int)subStr[idx];
        if (bitMap[pos] > 1) {
            return true;
        }
    }
    return false;
}

static void UpdateBitMap(uint8_t *bitMap, char s, bool isInsert)
{
    int pos = (int)s;
    if (isInsert) {
        bitMap[pos]++;
    } else {
        bitMap[pos]--;
    }
    return;
}

int lengthOfLongestSubstring(char *s)
{
    int strLen = (int)strlen(s);
    uint8_t bitMap[128] = {0};
    int maxLen = INT_MIN;

    if (strLen == 0) {
        return 0;
    }
    if (strLen == 1) {
        return 1;
    }

    int leftIdx = 0;
    int rightIdx = leftIdx + 1;
    UpdateBitMap(bitMap, s[leftIdx], true);
    UpdateBitMap(bitMap, s[rightIdx], true);
    while (rightIdx >= leftIdx && rightIdx < strLen) {
        int curLen = rightIdx - leftIdx + 1;
        if (IsCurWindowsDup(bitMap, &s[leftIdx], curLen)) {
            UpdateBitMap(bitMap, s[leftIdx], false);
            leftIdx++;
        } else {
            if (curLen > maxLen) {
                maxLen = curLen;
            }
            rightIdx++;
            UpdateBitMap(bitMap, s[rightIdx], true);
        }
    }
    return maxLen;
}
