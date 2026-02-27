/**
 * @file leetcode_backtrack_ut.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief leetcode backtrack ut
 * @version 0.1
 * @date 2026-02-27
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "gtest/gtest.h"
#include "leetcode_train.h"

class LeetcodeBackTrackTest : public testing::Test
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

TEST_F(LeetcodeBackTrackTest, 39_COMBINATION_SUM)
{
    // int candidates[] = {2, 3, 5};
    // int returnSize = 0;
    // int *returnColSizes = NULL;
    // combinationSum(candidates, sizeof(candidates) / sizeof(int), 8, &returnSize,
    // &returnColSizes);
}