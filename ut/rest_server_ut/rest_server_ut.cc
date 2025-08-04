/**
 * @file rest_server_ut.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief REST server demo UT
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "gtest/gtest.h"

TEST(RestServerTest, BasicAssertions)
{
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}