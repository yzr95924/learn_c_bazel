/**
 * @file iceberg_to_sql.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief Iceberg to SQL interface implementation
 * @version 0.1
 * @date 2025-08-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "iceberg_to_sql.h"

typedef struct {
    const char *col_name;
    const char *col_type;
    const char *col_constraints; // "NOT NULL", "PRIMARY KEY"
} SQLColDef;

static cJSON *GetMultiLevelItem(const cJSON *body, const char *item_path)
{
    char *item_path_copy = strdup(item_path);
    char *remain_ptr = NULL;
    char *cur_ptr = strtok_r(item_path_copy, ".", &remain_ptr);
    cJSON *cur_child_body = cJSON_GetObjectItemCaseSensitive(body, cur_ptr);
    DLOG(INFO) << "cur_ptr: " << cur_ptr;

    while (cur_child_body != NULL) {
        // move to the next level
        cur_ptr = strtok_r(NULL, ".", &remain_ptr);
        if (cur_ptr == NULL) {
            break;
        }
        DLOG(INFO) << "cur_ptr: " << cur_ptr;
        cur_child_body = cJSON_GetObjectItemCaseSensitive(cur_child_body, cur_ptr);
    }
    free(item_path_copy);
    return cur_child_body;
}

static int32_t GetFieldCnt(const cJSON *schema_fields)
{
    int32_t cnt = 0;
    cJSON *field_item = NULL;
    cJSON_ArrayForEach(field_item, schema_fields) {
        cnt++;
    }
    LOG(INFO) << "total fields cnt: " << cnt;
    return cnt;
}

static int32_t ParseFieldsArr(const cJSON *schema_fields, SQLColDef *sql_col_arr)
{
    cJSON *field_item = NULL;
    uint32_t idx = 0;
    cJSON_ArrayForEach(field_item, schema_fields) {
        cJSON *col_name = cJSON_GetObjectItemCaseSensitive(field_item, "name");
        sql_col_arr[idx].col_name = col_name->valuestring;
        cJSON *col_type = cJSON_GetObjectItemCaseSensitive(field_item, "type");
        sql_col_arr[idx].col_type = col_type->valuestring;
        LOG(INFO) << "col_name: " << sql_col_arr[idx].col_name
            << ", " << "col_type: " << sql_col_arr[idx].col_type;
        idx++;
    }
    return 0;
}

int32_t IcebergToSQLCreateTblSQL(const LCSCreateTblReq *req, uint8_t **sql_buf)
{
    UNUSED_PARAM(sql_buf)
    int32_t col_cnt = 0;
    const cJSON *body = req->body;
    LOG(INFO) << "convert Iceberg to SQL";
    cJSON *location = cJSON_GetObjectItemCaseSensitive(body, "location");
    if (cJSON_IsString(location)) {
        LOG(INFO) << "get location: " << location->valuestring;
    }

    LOG(INFO) << "start to parse schema";
    cJSON *schema_fields = GetMultiLevelItem(body, "schema.fields");
    if (!cJSON_IsArray(schema_fields)) {
        LOG(ERROR) << "schema.fields is not array";
        return EINVAL;
    }
    col_cnt = GetFieldCnt(schema_fields);
    SQLColDef *col_def_arr = (SQLColDef*)malloc(sizeof(SQLColDef) * col_cnt);

    ParseFieldsArr(schema_fields, col_def_arr);
    free(col_def_arr);
    return 0;
}

void IcebergToSQLFreeBuf(uint8_t **sql_buf)
{
    UNUSED_PARAM(sql_buf)
    return;
}