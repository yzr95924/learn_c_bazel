/**
 * @file 148_sort_list.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 148. 排序链表 https://leetcode.cn/problems/sort-list/description/
 * @version 0.1
 * @date 2026-02-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_linked_list.h"

typedef struct ListNode ListNode;

static ListNode *MergerTwoSortedList(ListNode *list1, ListNode *list2)
{
    ListNode *dummyNode = (ListNode *)calloc(1, sizeof(ListNode));
    ListNode *curList1Node = list1;
    ListNode *curList2Node = list2;
    if (curList1Node == NULL) {
        return curList2Node;
    }
    if (curList2Node == NULL) {
        return curList1Node;
    }

    ListNode *curNode = dummyNode;
    while (curList1Node != NULL && curList2Node != NULL) {
        if (curList1Node->val <= curList2Node->val) {
            curNode->next = curList1Node;
            curList1Node = curList1Node->next;
        } else {
            curNode->next = curList2Node;
            curList2Node = curList2Node->next;
        }
        curNode = curNode->next;
    }
    if (curList1Node != NULL) {
        curNode->next = curList1Node;
    }
    if (curList2Node != NULL) {
        curNode->next = curList2Node;
    }
    ListNode *ans = dummyNode->next;
    free(dummyNode);
    return ans;
}

static ListNode *SortPartList(ListNode *head, ListNode *tail)
{
    // 左闭右开
    if (head == NULL) {
        return head;
    }
    if (head->next == tail) {
        head->next = NULL;
        return head;
    }
    ListNode *slow = head, *fast = head;
    while (fast != tail) {
        slow = slow->next;
        fast = fast->next;
        if (fast != tail) {
            fast = fast->next;
        }
    }
    ListNode *mid = slow;
    return MergerTwoSortedList(SortPartList(head, mid), SortPartList(mid, tail));
}

struct ListNode *sortList(struct ListNode *head)
{
    if (head == NULL || head->next == NULL) {
        return head;
    }
    // 左闭右开，针对原本的list，右边开的话，tail是NULL
    return SortPartList(head, NULL);
}