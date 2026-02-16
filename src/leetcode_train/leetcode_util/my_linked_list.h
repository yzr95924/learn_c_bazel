/**
 * @file my_linked_list.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief my linked list
 * @version 0.1
 * @date 2026-02-16
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef MY_LINKED_LIST_H
#define MY_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int MyDLListValType;

struct MyDLListNode {
    MyDLListValType data;
    struct MyDLListNode *next;
    struct MyDLListNode *prev;
};
typedef struct MyDLListNode MyDLListNode;

typedef struct {
    MyDLListNode *head;
    MyDLListNode *tail;
    int curSize;
} MyDLList;

static MyDLList *MyInitDLList()
{
    MyDLList *dlListPtr = (MyDLList *)calloc(1, sizeof(MyDLList));
    dlListPtr->head = NULL;
    dlListPtr->tail = NULL;
    dlListPtr->curSize = 0;
    return dlListPtr;
}

static void MyFreeDLList(MyDLList *dLListPtr)
{
    MyDLListNode *curNode = dLListPtr->head;
    MyDLListNode *delNode = NULL;

    while (curNode != NULL) {
        delNode = curNode;
        curNode = curNode->next;
        free(delNode);
    }

    free(dLListPtr);
    return;
}

static MyDLListNode *MyInsertHeadDLList(MyDLList *dLListPtr, MyDLListValType *inVal)
{
    MyDLListNode *newNode = (MyDLListNode *)calloc(1, sizeof(MyDLListNode));
    memcpy(&newNode->data, inVal, sizeof(MyDLListValType));
    newNode->next = NULL;
    newNode->prev = NULL;

    if (dLListPtr->curSize == 0) {
        dLListPtr->tail = newNode;
    } else {
        dLListPtr->head->prev = newNode;
        newNode->next = dLListPtr->head;
    }

    dLListPtr->head = newNode;
    dLListPtr->curSize++;
    return newNode;
}

static MyDLListNode *MyInsertTailDLList(MyDLList *dLListPtr, MyDLListValType *inVal)
{
    MyDLListNode *newNode = (MyDLListNode *)calloc(1, sizeof(MyDLListNode));
    memcpy(&newNode->data, inVal, sizeof(MyDLListValType));
    newNode->next = NULL;
    newNode->prev = NULL;

    if (dLListPtr->curSize == 0) {
        dLListPtr->head = newNode;
    } else {
        dLListPtr->tail->next = newNode;
        newNode->prev = dLListPtr->tail;
    }

    dLListPtr->tail = newNode;
    dLListPtr->curSize++;
    return newNode;
}

static MyDLListNode *MyInsertAfterNodeDLList(MyDLList *dLListPtr, MyDLListNode *targetNode, MyDLListNode *inVal)
{
    MyDLListNode *newNode = (MyDLListNode *)calloc(1, sizeof(MyDLListNode));
    memcpy(newNode, inVal, sizeof(MyDLListNode));
    newNode->next = NULL;
    newNode->prev = NULL;

    if (targetNode == dLListPtr->tail) {
        newNode->next = NULL;
        dLListPtr->tail = newNode;
    } else {
        newNode->next = targetNode->next;
        targetNode->next->prev = newNode;
    }

    newNode->prev = targetNode;
    targetNode->next = newNode;
    dLListPtr->curSize++;
    return newNode;
}

static bool MyFindDLList(MyDLList *dLListPtr, MyDLListValType *inVal, MyDLListNode *findNode)
{
    if (dLListPtr->curSize == 0) {
        return false;
    }

    MyDLListNode *curNode = dLListPtr->head;
    while (curNode != NULL) {
        if (memcmp(&curNode->data, inVal, sizeof(MyDLListValType)) == 0) {
            // equal
            memcpy(findNode, curNode, sizeof(MyDLListNode));
            return true;
        }
        // not equal
        curNode = curNode->next;
    }
    return false;
}

static bool MyDelDLListWithPtr(MyDLList *dLListPtr, MyDLListNode *targetNode)
{
    if (dLListPtr->curSize == 0) {
        return false;
    }

    if (targetNode == dLListPtr->head) {
        dLListPtr->head = targetNode->next;
    } else {
        targetNode->prev->next = targetNode->next;
    }

    if (targetNode == dLListPtr->tail) {
        dLListPtr->tail = targetNode->prev;
    } else {
        targetNode->next->prev = targetNode->prev;
    }

    dLListPtr->curSize--;
    free(targetNode);
    return true;
}

#endif