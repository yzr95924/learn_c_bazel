/**
 * @file 160_remove_nth_from_end.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief implementation of 19. 删除链表的倒数第 N 个结点
 * @version 0.1
 * @date 2026-02-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_linked_list.h"

typedef struct ListNode ListNode;

static int GetListSize(ListNode *head)
{
    ListNode *tmpNode = head;
    int listSize = 0;
    while (tmpNode != NULL) {
        listSize++;
        tmpNode = tmpNode->next;
    }
    return listSize;
}

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
    // use dummy node
    ListNode *dummyNode = (ListNode *)calloc(1, sizeof(ListNode));
    dummyNode->val = 0;
    dummyNode->next = head;
    int listSize = GetListSize(head);
    ListNode *curNode = dummyNode;
    ListNode *delNode = NULL;
    for (int idx = 0; idx < listSize - n; idx++) {
        curNode = curNode->next;
    }
    // 因为n >= 1，所以保证curNode->next不会为NULL
    delNode = curNode->next;
    curNode->next = curNode->next->next;
    free(delNode);
    ListNode *ansHead = dummyNode->next;
    free(dummyNode);
    return ansHead;
}