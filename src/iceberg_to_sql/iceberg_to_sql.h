/**
 * @file iceberg_to_sql.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief convert Iceberg to SQL
 * @version 0.1
 * @date 2025-08-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LEARN_C_BAZEL_ICEBERG_TO_SQL
#define LEARN_C_BAZEL_ICEBERG_TO_SQL

#include "cJSON.h"
#include "common_util.h"
#include "glog/logging.h"

#define MAX_ICEBERG_TYPE_NAME_LEN 20
#define MAX_ICEBERG_WAREHOUSE_NAME_LEN 30

// select
// attach_formation_table('testing','sift1w','{"type":"local","warehouse":"/tmp/iceberg_warehouse"}','testing/sift1w');
// select detach_formation_table('testing','sift1w');

typedef struct {
    char type[MAX_ICEBERG_TYPE_NAME_LEN];
    char warehouse_name[MAX_ICEBERG_WAREHOUSE_NAME_LEN];
} LCSIcebergServerConfig;

typedef struct {
    char ns_name[MAX_NS_NAME_LEN];
    char tbl_name[MAX_TBL_NAME_LEN];
    const cJSON *body;
    LCSIcebergServerConfig connConfig;
} LCSCreateTblReq;

typedef struct {
    char ns_name[MAX_NS_NAME_LEN];
    char tbl_name[MAX_TBL_NAME_LEN];
} LCSDelTblReq;

/**
 * @brief for create tbl req, convert Iceberg to SQL
 *
 * @param[in] req create tbl req
 * @param[out] sql_buf create tbl sql
 * @return int32_t inner erro code
 */
int32_t IcebergToSQLCreateTblSQL(const LCSCreateTblReq *req, uint8_t **sql_buf);

/**
 * @brief for create tbl req, convert Iceberg to SQL (new version)
 *
 * @param[in] req create tbl req
 * @param[out] sql_buf create tbl sql
 * @return int32_t inner error code
 */
int32_t IcebergToSQLCreateTblSQLNew(const LCSCreateTblReq *req, uint8_t **sql_buf);

int32_t IcebergToSQLDelTblSQLNew(const LCSDelTblReq *req, uint8_t **sql_buf);

/**
 * @brief free SQL buffer
 *
 * @param[in] sql_buf sql buffer
 */
void IcebergToSQLFreeBuf(uint8_t **sql_buf);

#endif