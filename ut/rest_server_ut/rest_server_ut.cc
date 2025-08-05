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
#include "rest_server.h"

constexpr const char* kTestName = "RestServerTest";
class RestServerTest : public testing::Test {
    protected:
        void SetUp() override {
            // run at the begining of each test case
            return;
        }

        void TearDown() override {
            // run at the end of each test case
            return;
        }

        static void SetUpTestSuite() {
            // run for the whole test class
            google::InitGoogleLogging(kTestName);
            FLAGS_logtostderr = true;
            FLAGS_colorlogtostderr = true;
            FLAGS_colorlogtostdout = true;
            return;
        }

        static void TearDownTestSuite() {
            // run for the whole test class
            google::ShutdownGoogleLogging();
            return;
        }
};

TEST_F(RestServerTest, RestServerInit_OK)
{
    int32_t ret = 0;
    ret = RestServerInit();
    EXPECT_EQ(ret, 0);
    RestServerDestroy();
}