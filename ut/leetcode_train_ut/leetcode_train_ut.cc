/**
 * @file leetcode_train_ut.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief leetcode train ut
 * @version 0.1
 * @date 2026-02-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "gtest/gtest.h"
#include "leetcode_train.h"

class LeetcodeTrainTest : public testing::Test
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

TEST_F(LeetcodeTrainTest, LeetcodeTrainTest_TEST)
{
    int32_t ret = 0;
    EXPECT_EQ(1, ret + 1);
}