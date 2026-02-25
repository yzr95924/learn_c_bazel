/**
 * @file 146_lru_cache.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 146. LRU 缓存 https://leetcode.cn/problems/lru-cache/description/
 * @version 0.1
 * @date 2026-02-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_app.h"

static bool HashTblGet(LRUCache *obj, int key, HashTblItem **retItem)
{
    HashTblItem *tmpItem;
    HashTblItem **hashTbl = obj->hashTbl;
    HASH_FIND_INT(*hashTbl, &key, tmpItem);
    if (tmpItem == NULL) {
        *retItem = NULL;
        return false;
    }

    *retItem = tmpItem;
    return true;
}

static void HashTblInsert(LRUCache *obj, int key, DDListNode *inNode)
{
    HashTblItem *tmpHashItem;

    // update uthash tbl -> implicitly modify *hashTblPtr
    HashTblItem **hashTbl = obj->hashTbl;
    HASH_FIND_INT(*hashTbl, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (HashTblItem *)calloc(1, sizeof(HashTblItem));
        tmpHashItem->hashKey = key;
        HASH_ADD_INT(*hashTbl, hashKey, tmpHashItem);
    }
    tmpHashItem->hashVal = inNode;
    return;
}

static void HashTblFree(HashTblItem **hashTbl)
{
    HashTblItem *curItem;
    HashTblItem *tmpItem;

    HASH_ITER(hh, *hashTbl, curItem, tmpItem)
    {
        HASH_DEL(*hashTbl, curItem);
        free(curItem);
    }
    free(hashTbl);
    return;
}

static void DDListInsertHead(LRUCache *obj, DDListNode *inNode)
{
    if (obj->curSize == 0) {
        obj->listTail = inNode;
        obj->listHead = inNode;
    } else {
        DDListNode *curHead = obj->listHead;
        curHead->next = inNode;
        inNode->prev = curHead;
        inNode->next = NULL;
        obj->listHead = inNode;
    }

    obj->curSize++;
    return;
}

static void DDListRemoveFromList(LRUCache *obj, DDListNode *inNode)
{
    DDListNode *prevNode = inNode->prev;
    DDListNode *nextNode = inNode->next;
    if (obj->listHead == inNode) {
        obj->listHead = prevNode;
        if (prevNode != NULL) {
            prevNode->next = NULL;
        }
    } else if (obj->listTail == inNode) {
        obj->listTail = nextNode;
        if (nextNode != NULL) {
            nextNode->prev = NULL;
        }
    } else {
        if (prevNode != NULL) {
            prevNode->next = nextNode;
        }
        if (nextNode != NULL) {
            nextNode->prev = prevNode;
        }
    }
    obj->curSize--;
    inNode->prev = NULL;
    inNode->next = NULL;
    return;
}

static void DDlistFree(LRUCache *obj)
{
    DDListNode *curNode = obj->listHead;
    while (curNode != NULL) {
        DDListNode *nextNode = curNode->next;
        free(curNode);
        curNode = nextNode;
    }
    obj->curSize = 0;
    return;
}

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *lruCache = (LRUCache *)calloc(1, sizeof(LRUCache));
    lruCache->capacity = capacity;
    lruCache->hashTbl = (HashTblItem **)calloc(1, sizeof(HashTblItem *));
    lruCache->listHead = NULL;
    lruCache->listTail = NULL;
    lruCache->curSize = 0;
    return lruCache;
}

int lRUCacheGet(LRUCache *obj, int key)
{
    HashTblItem *retItem;
    bool isFind = HashTblGet(obj, key, &retItem);
    if (!isFind) {
        return -1;
    }

    DDListNode *curNode = retItem->hashVal;
    DDListRemoveFromList(obj, curNode);
    DDListInsertHead(obj, curNode);
    return curNode->val;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    HashTblItem *retItem;
    bool isFind = HashTblGet(obj, key, &retItem);
    if (isFind) {
        // in-place update
        retItem->hashVal->val = value;
        HashTblInsert(obj, key, retItem->hashVal);
        DDListRemoveFromList(obj, retItem->hashVal);
        DDListInsertHead(obj, retItem->hashVal);
        return;
    }

    if (obj->curSize == obj->capacity) {
        DDListNode *replaceNode = obj->listTail;
        HashTblGet(obj, replaceNode->key, &retItem);
        HASH_DEL(*(obj->hashTbl), retItem);
        free(retItem);
        DDListRemoveFromList(obj, replaceNode);
    }

    DDListNode *newNode = (DDListNode *)calloc(1, sizeof(DDListNode));
    newNode->key = key;
    newNode->val = value;
    DDListInsertHead(obj, newNode);
    HashTblInsert(obj, key, newNode);
    return;
}

void lRUCacheFree(LRUCache *obj)
{
    HashTblFree(obj->hashTbl);
    DDlistFree(obj);
    free(obj);
    return;
}