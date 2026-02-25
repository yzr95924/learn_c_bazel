/**
 * @file leetcode_app.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief leetcode application question header
 * @version 0.1
 * @date 2026-02-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LEETCODE_APP
#define LEETCODE_APP

#include "common_util.h"
#include "uthash.h"

// 146. LRU 缓存
// https://leetcode.cn/problems/lru-cache/description/

struct DDListNode {
    int key;
    int val;
    struct DDListNode *next;
    struct DDListNode *prev;
};
typedef struct DDListNode DDListNode;

typedef struct {
    int hashKey;
    DDListNode *hashVal;
    UT_hash_handle hh;
} HashTblItem;

typedef struct {
    int capacity;
    HashTblItem **hashTbl;
    DDListNode *listHead;
    DDListNode *listTail;
    int curSize;
} LRUCache;

LRUCache *lRUCacheCreate(int capacity);
int lRUCacheGet(LRUCache *obj, int key);
void lRUCachePut(LRUCache *obj, int key, int value);
void lRUCacheFree(LRUCache *obj);

#endif