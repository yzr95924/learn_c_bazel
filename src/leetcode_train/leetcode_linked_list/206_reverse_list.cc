/**
 * @file 206_reverse_list.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief
 * @version 0.1
 * @date 2026-02-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_linked_list.h"

typedef struct ListNode ListNode;

struct ListNode *reverseList(struct ListNode *head)
{
    ListNode *curNode = head;
    ListNode *prevNode = NULL;
    ListNode *nextNode = NULL;
    while (curNode != NULL) {
        // save the next node
        nextNode = curNode->next;
        // change the ptr to prev node
        curNode->next = prevNode;
        // save the current node as the previous node for next round
        prevNode = curNode;
        // set the current node as the next node
        curNode = nextNode;
    }
    return prevNode;
}