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

// 19. 删除链表的倒数第 N 个结点
// https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/
struct ListNode *removeNthFromEnd(struct ListNode *head, int n);

// 21. 合并两个有序链表
// https://leetcode.cn/problems/merge-two-sorted-lists/description/
struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2);

// 23. 合并K个排序链表
// https://leetcode.cn/problems/merge-k-sorted-lists/description/
struct ListNode *mergeKLists(struct ListNode **lists, int listsSize);

// 141. 环形链表
// https://leetcode.cn/problems/linked-list-cycle/description/
bool hasCycle(struct ListNode *head);

// 160. 相交链表
// https://leetcode.cn/problems/intersection-of-two-linked-lists/description
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB);

// 206. 反转链表
// https://leetcode.cn/problems/reverse-linked-list/description/
struct ListNode *reverseList(struct ListNode *head);

#endif
