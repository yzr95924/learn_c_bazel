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

constexpr const char *k_ns_name = "ns1";
constexpr const char *k_tbl_name = "my_table";
constexpr const char *k_warehouse_type = "local";
constexpr const char *k_warehouse_path = "/tmp/iceberg_warehouse";
constexpr const char *k_test_str_1 = "test_1";
constexpr const char *k_test_str_2 = "test_2";

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
            return;
        }

        static void TearDownTestSuite() {
            // run for the whole test class
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
    json_file_size = (uint64_t)ftell(json_fd);
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

TEST_F(IcebergToSQLTest, IcebergToSQLDelTblSQLNew_NORMAL)
{
    LCSDelTblReq req = {};
    memcpy(req.ns_name, k_ns_name, strlen(k_ns_name));
    memcpy(req.tbl_name, k_tbl_name, strlen(k_tbl_name));

    int32_t ret = 0;
    uint8_t *sql_buf = NULL;
    ret = IcebergToSQLDelTblSQLNew(&req, &sql_buf);
    EXPECT_EQ(ret, 0);

    IcebergToSQLFreeBuf(&sql_buf);
}

TEST_F(IcebergToSQLTest, IcebergToSQLCreateTblSQLNew_NORMAL)
{
    LCSCreateTblReq req = {};
    memcpy(req.connConfig.type, k_warehouse_type,
        strlen(k_warehouse_type));
    memcpy(req.connConfig.warehouse_name, k_warehouse_path,
        strlen(k_warehouse_path));
    memcpy(req.ns_name, k_ns_name, strlen(k_ns_name));
    memcpy(req.tbl_name, k_tbl_name, strlen(k_tbl_name));

    int32_t ret = 0;
    uint8_t *sql_buf = NULL;
    ret = IcebergToSQLCreateTblSQLNew(&req, &sql_buf);
    EXPECT_EQ(ret, 0);

    IcebergToSQLFreeBuf(&sql_buf);

    const char *test_str = NULL;
    test_str = k_test_str_1;
    LOG(INFO) << test_str;
    test_str = k_test_str_2;
    LOG(INFO) << test_str;
}