/**
 * @file c_my_hash.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief leetcode linked list question header
 * @version 0.1
 * @date 2023-06-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_LINKED_LIST_H
#define LEETCODE_LINKED_LIST_H

#include "common_util.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode ListNode;

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB);

#endif
