/**
 * @file 160_get_intersection_node.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 160. 相交链表
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
    ListNode *curNode = head;
    int listSize = 0;
    while (curNode != NULL) {
        listSize++;
        curNode = curNode->next;
    }
    return listSize;
}

static void ForwardNNode(ListNode *head, int n, ListNode **retNode)
{
    ListNode *curNode = head;
    for (int idx = 0; idx < n; idx++) {
        curNode = curNode->next;
    }
    *retNode = curNode;
    return;
}

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    ListNode *curList1Node = headA;
    ListNode *curList2Node = headB;
    int list1Size = GetListSize(headA);
    int list2Size = GetListSize(headB);
    int n = 0;
    if (list2Size >= list1Size) {
        n = list2Size - list1Size;
        ForwardNNode(headB, n, &curList2Node);
    } else {
        n = list1Size - list2Size;
        ForwardNNode(headA, n, &curList1Node);
    }

    ListNode *retNode = NULL;
    while (curList1Node != NULL && curList2Node != NULL) {
        if (curList1Node == curList2Node) {
            retNode = curList1Node;
            break;
        }
        curList1Node = curList1Node->next;
        curList2Node = curList2Node->next;
    }
    return retNode;
}