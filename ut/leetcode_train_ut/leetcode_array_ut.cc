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

class LeetcodeArrayTest : public testing::Test
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

TEST_F(LeetcodeArrayTest, 33_SEARCH)
{
    int testArr[] = {3, 1};
    int target = 1;
    search_33(testArr, (sizeof(testArr) / sizeof(int)), target);
}