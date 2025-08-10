/**
 * @file rest_server_ut.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief iceberg to sql UT
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "gtest/gtest.h"
#include "iceberg_to_sql.h"

constexpr const char *kTestName = "IcebergToSQLTest";
class IcebergToSQLTest : public testing::Test {
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
            FLAGS_minloglevel = -1;  // 启用所有 DEBUG 日志（级别设为 -1）
            return;
        }

        static void TearDownTestSuite() {
            // run for the whole test class
            google::ShutdownGoogleLogging();
            return;
        }
};

TEST_F(IcebergToSQLTest, IcebergToSQLCreateTblSQL_NORMAL)
{
    constexpr const char* json_path = "./data/create_tbl_req.json";
    constexpr const char* ns_name = "ns1";
    constexpr const char* tbl_name = "my_table";
    FILE* json_fd = fopen(json_path, "rb");
    int32_t ret = 0;
    uint64_t json_file_size = 0;
    uint8_t* json_data_str_buf = NULL;
    uint8_t* sqlBuf = NULL;
    LCSCreateTblReq req = {};

    if (json_fd == NULL) {
        LOG(ERROR) << "cannot open json failed, " << json_path;
        return;
    }
    LOG(INFO) << "open json file done";
    fseek(json_fd, 0, SEEK_END);
    json_file_size = ftell(json_fd);
    fseek(json_fd, 0, SEEK_SET);

    json_data_str_buf = (uint8_t*)malloc(json_file_size + 1);
    fread(json_data_str_buf, 1, json_file_size, json_fd);
    json_data_str_buf[json_file_size] = '\0';

    cJSON* body = cJSON_Parse((char*)json_data_str_buf);
    memcpy(req.ns_name, ns_name, strlen(ns_name));
    memcpy(req.tbl_name, tbl_name, strlen(tbl_name));
    req.body = body;

    ret = IcebergToSQLCreateTblSQL(&req, &sqlBuf);

    EXPECT_EQ(ret, 0);
    fclose(json_fd);
    cJSON_Delete(body);
    free(json_data_str_buf);
}