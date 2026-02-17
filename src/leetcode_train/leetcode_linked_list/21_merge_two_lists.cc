/**
 * @file 21_merge_two_lists.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief implementation of 21. 合并两个有序链表
 * @version 0.1
 * @date 2026-02-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_linked_list.h"

typedef struct ListNode ListNode;

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    ListNode *dummyNode = (ListNode *)calloc(1, sizeof(ListNode));
    ListNode *curList1Node = list1;
    ListNode *curList2Node = list2;
    if (curList1Node == NULL) {
        return list2;
    }
    if (curList2Node == NULL) {
        return list1;
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