/**
 * @file 142_detect_cycle.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 142. 环形链表 II
 * @version 0.1
 * @date 2026-02-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_linked_list.h"
#include "uthash.h"

typedef struct {
    void *hashKey;
    int hashVal;
    UT_hash_handle hh;
} PtrHashTblItem;
static PtrHashTblItem *g_hashTbl = NULL;

static void InsertPtrToHashTbl(void *key)
{
    PtrHashTblItem *tmpHashItem = NULL;
    tmpHashItem = (PtrHashTblItem *)calloc(1, sizeof(PtrHashTblItem));
    tmpHashItem->hashKey = key;
    tmpHashItem->hashVal = 0;
    HASH_ADD_PTR(g_hashTbl, hashKey, tmpHashItem);
}

static bool FindPtrHashTbl(void *key)
{
    PtrHashTblItem *tmpHashItem = NULL;
    HASH_FIND_PTR(g_hashTbl, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        return false;
    }
    return true;
}

static void DelPtrHashTblAllItems()
{
    PtrHashTblItem *curItem = NULL;
    PtrHashTblItem *tmpItem = NULL;
    HASH_ITER(hh, g_hashTbl, curItem, tmpItem)
    {
        HASH_DEL(g_hashTbl, curItem);
        free(curItem);
    }
    return;
}

typedef struct ListNode ListNode;

struct ListNode *detectCycle(struct ListNode *head)
{
    ListNode *curNode = head;
    bool isFind = false;
    while (curNode != NULL) {
        isFind = FindPtrHashTbl(curNode);
        if (isFind) {
            break;
        } else {
            InsertPtrToHashTbl(curNode);
        }
        curNode = curNode->next;
    }
    DelPtrHashTblAllItems();
    if (isFind) {
        return curNode;
    }
    return NULL;
}