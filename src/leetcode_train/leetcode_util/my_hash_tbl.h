/**
 * @file c_my_hash.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my hash table
 * @version 0.1
 * @date 2023-06-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MY_HASH_TBL_H
#define MY_HASH_TBL_H

#include "uthash.h"

typedef int MyHashValType;

typedef struct {
    int hashKey;
    MyHashValType hashVal;
    UT_hash_handle hh;
} MyIntHashTblItem;

/**
 *********************************************
 ***               for int key hash table
 *********************************************
 */

static MyIntHashTblItem **My_InitIntHashTbl()
{
    // alloc a head ptr for a uthash tbl
    MyIntHashTblItem **hashTblPtr = (MyIntHashTblItem **)calloc(1, sizeof(MyIntHashTblItem *));
    // init the head to NULL
    *hashTblPtr = NULL;
    return hashTblPtr;
}

static MyIntHashTblItem *My_InsertIntHashTbl(MyIntHashTblItem **hashTblPtr, int key, MyHashValType *inVal)
{
    MyIntHashTblItem *tmpHashItem;

    // update uthash tbl -> implicitly modify *hashTblPtr
    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (MyIntHashTblItem *)calloc(1, sizeof(MyIntHashTblItem));
        tmpHashItem->hashKey = key;
        HASH_ADD_INT(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(MyHashValType));
    return tmpHashItem;
}

static bool My_FindIntHashTbl(MyIntHashTblItem **hashTblPtr, int key, MyIntHashTblItem **ret)
{
    MyIntHashTblItem *tmpHashItem = NULL;
    HASH_FIND_INT(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        *ret = NULL;
        return false;
    }

    *ret = tmpHashItem;
    return true;
}

static void My_DelIntHashTbl(MyIntHashTblItem **hashTblPtr, MyIntHashTblItem *hashItem)
{
    HASH_DEL(*hashTblPtr, hashItem);
    free(hashItem);
    return;
}

static void My_FreeIntHashTbl(MyIntHashTblItem **hashTblPtr)
{
    MyIntHashTblItem *curItem;
    MyIntHashTblItem *tmpItem;

    HASH_ITER(hh, *hashTblPtr, curItem, tmpItem)
    {
        HASH_DEL(*hashTblPtr, curItem);
        free(curItem);
    }
    free(hashTblPtr);
    return;
}

/**
 *********************************************
 ***               for ptr key hash table
 *********************************************
 */

typedef struct {
    void *hashKey;
    MyHashValType hashVal;
    UT_hash_handle hh;
} MyPtrHashTblItem;

static MyPtrHashTblItem **My_InitPtrHashTbl()
{
    MyPtrHashTblItem **hashTblPtr = (MyPtrHashTblItem **)calloc(1, sizeof(MyPtrHashTblItem *));
    *hashTblPtr = NULL;
    return hashTblPtr;
}

static void My_InsertPtrHashTbl(MyPtrHashTblItem **hashTblPtr, void *key, MyHashValType *inVal)
{
    MyPtrHashTblItem *tmpHashItem = NULL;
    HASH_FIND_PTR(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (MyPtrHashTblItem *)calloc(1, sizeof(MyPtrHashTblItem));
        tmpHashItem->hashKey = key;
        HASH_ADD_PTR(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(MyHashValType));
    return;
}

static bool My_FindPtrHashTbl(MyPtrHashTblItem **hashTblPtr, void *key, MyPtrHashTblItem **ret)
{
    MyPtrHashTblItem *tmpHashItem = NULL;
    HASH_FIND_PTR(*hashTblPtr, &key, tmpHashItem);
    if (tmpHashItem == NULL) {
        *ret = NULL;
        return false;
    }

    *ret = tmpHashItem;
    return true;
}

static void My_DelPtrHashTbl(MyPtrHashTblItem **hashTblPtr, MyPtrHashTblItem *hashItem)
{
    HASH_DEL(*hashTblPtr, hashItem);
    free(hashItem);
    return;
}

static void My_FreePtrHashTbl(MyPtrHashTblItem **hashTblPtr)
{
    MyPtrHashTblItem *curItem;
    MyPtrHashTblItem *tmpItem;

    HASH_ITER(hh, *hashTblPtr, curItem, tmpItem)
    {
        HASH_DEL(*hashTblPtr, curItem);
        free(curItem);
    }
    free(hashTblPtr);
    return;
}

/**
 *********************************************
 ***               for str key hash table
 *********************************************
 */

#define MAX_HASH_KEY_SIZE 32

typedef struct {
    char hashKey[MAX_HASH_KEY_SIZE];
    MyHashValType hashVal;
    UT_hash_handle hh;
} My_StrHashTblItem;

static My_StrHashTblItem **My_InitStrHashTbl()
{
    My_StrHashTblItem **hashTblPtr = (My_StrHashTblItem **)calloc(1, sizeof(My_StrHashTblItem *));
    *hashTblPtr = NULL;
    return hashTblPtr;
}

static void My_InsertStrHashTbl(My_StrHashTblItem **hashTblPtr, const char *key, MyHashValType *inVal)
{
    My_StrHashTblItem *tmpHashItem = NULL;
    HASH_FIND_STR(*hashTblPtr, key, tmpHashItem);
    if (tmpHashItem == NULL) {
        tmpHashItem = (My_StrHashTblItem *)calloc(1, sizeof(My_StrHashTblItem));
        strcpy(tmpHashItem->hashKey, key);
        HASH_ADD_STR(*hashTblPtr, hashKey, tmpHashItem);
    }
    memcpy(&tmpHashItem->hashVal, inVal, sizeof(MyHashValType));
    return;
}

static bool My_FindStrHashTbl(My_StrHashTblItem **hashTblPtr, const char *key, My_StrHashTblItem **ret)
{
    My_StrHashTblItem *tmpHashItem = NULL;
    HASH_FIND_STR(*hashTblPtr, key, tmpHashItem);
    if (tmpHashItem == NULL) {
        *ret = NULL;
        return false;
    }

    *ret = tmpHashItem;
    return true;
}

static void My_DelStrHashTbl(My_StrHashTblItem **hashTblPtr, My_StrHashTblItem *hashItem)
{
    HASH_DEL(*hashTblPtr, hashItem);
    free(hashItem);
    return;
}

static void My_FreeStrHashTbl(My_StrHashTblItem **hashTblPtr)
{
    My_StrHashTblItem *curItem;
    My_StrHashTblItem *tmpItem;

    HASH_ITER(hh, *hashTblPtr, curItem, tmpItem)
    {
        HASH_DEL(*hashTblPtr, curItem);
        free(curItem);
    }
    free(hashTblPtr);
    return;
}

#endif