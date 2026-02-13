/**
 * @file ut_main.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief for ut test main entrance
 * @version 0.1
 * @date 2026-02-01
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "common_util.h"
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    UNUSED_PARAM(argc);

    testing::InitGoogleTest();

    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    FLAGS_colorlogtostderr = true;
    FLAGS_colorlogtostdout = true;
    FLAGS_minloglevel = -1; // 启用所有 DEBUG 日志（级别设为 -1）

    int32_t ret = RUN_ALL_TESTS();

    google::ShutdownGoogleLogging();
    return ret;
}
