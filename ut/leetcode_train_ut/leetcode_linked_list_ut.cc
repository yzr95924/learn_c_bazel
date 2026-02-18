/**
 * @file leetcode_train_ut.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief leetcode linked list ut
 * @version 0.1
 * @date 2026-02-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "gtest/gtest.h"
#include "leetcode_train.h"

class LeetcodeLinkedListTest : public testing::Test
{
   protected:
    void SetUp() override
    {
        // run at the begining of each test case
        return;
    }

    void TearDown() override
    {
        // run at the end of each test case
        return;
    }

    static void SetUpTestSuite()
    {
        // run for the whole test class
        return;
    }

    static void TearDownTestSuite()
    {
        // run for the whole test class
        return;
    }
};

typedef struct ListNode ListNode;

static void ConvertArrToLinkedList(int *intputArr, int arrSize, ListNode **head)
{
    ListNode *dummyNode = (ListNode *)calloc(1, sizeof(ListNode));
    ListNode *prevNode = dummyNode;
    ListNode *curNode = NULL;
    for (int idx = 0; idx < arrSize; idx++) {
        curNode = (ListNode *)calloc(1, sizeof(ListNode));
        curNode->val = intputArr[idx];
        curNode->next = NULL;
        prevNode->next = curNode;
        prevNode = curNode;
    }
    *head = dummyNode->next;
    free(dummyNode);
    return;
}

static void FreeLinkedList(ListNode *head)
{
    ListNode *nextNode = NULL;
    ListNode *curNode = head;
    while (curNode != NULL) {
        nextNode = curNode->next;
        free(curNode);
        curNode = nextNode;
    }
    return;
}

TEST_F(LeetcodeLinkedListTest, 141_SORT_LIST)
{
    int arr[3] = {1, 3, 2};
    ListNode *head = NULL;
    ConvertArrToLinkedList(arr, 3, &head);
    ListNode *sortRet = sortList(head);
    ListNode *curNode = sortRet;
    while (curNode != NULL) {
        printf("%d\n", curNode->val);
        curNode = curNode->next;
    }
    FreeLinkedList(head);
}