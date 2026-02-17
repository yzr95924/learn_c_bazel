/**
 * @file 234_is_palindrome.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 234. 回文链表 https://leetcode.cn/problems/palindrome-linked-list/description/
 * @version 0.1
 * @date 2026-02-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_linked_list.h"

typedef struct ListNode ListNode;

static size_t GetListSize(ListNode *head)
{
    ListNode *curNode = head;
    size_t listSize = 0;
    while (curNode != NULL) {
        listSize++;
        curNode = curNode->next;
    }
    return listSize;
}

static bool CheckArrIsPalindrome(int *listArr, size_t listSize)
{
    size_t startIdx = 0;
    size_t endIdx = listSize - 1;
    size_t cmpCnt = listSize / 2;
    for (size_t cmpNum = 0; cmpNum < cmpCnt; cmpNum++) {
        if (listArr[startIdx] != listArr[endIdx]) {
            return false;
        }
        startIdx++;
        endIdx--;
    }
    return true;
}

bool isPalindrome(struct ListNode *head)
{
    size_t listSize = GetListSize(head);
    int *listArr = (int *)calloc(listSize, sizeof(int));
    ListNode *curNode = head;
    bool isPalindrome = false;
    int idx = 0;
    while (curNode != NULL) {
        listArr[idx] = curNode->val;
        curNode = curNode->next;
        idx++;
    }
    isPalindrome = CheckArrIsPalindrome(listArr, listSize);
    free(listArr);
    return isPalindrome;
}