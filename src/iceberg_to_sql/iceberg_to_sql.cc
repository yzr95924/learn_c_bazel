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
#include "pg_client.h"

static const char iceberg_server_config_tmpl_str[] =
    "{\"type\":\"%s\",\"warehouse\":\"%s\"}";

static const char create_tbl_req_tmpl_str[] =
    "select attach_formation_table('%s', '%s', '%s', '%s/%s');";

static const char del_tbl_req_tmpl_str[] =
    "select detach_formation_table('%s', '%s');";

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
    UNUSED_PARAM(sql_buf);
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
    SQLColDef *col_def_arr = (SQLColDef*)malloc(sizeof(SQLColDef) * (size_t)col_cnt);

    ParseFieldsArr(schema_fields, col_def_arr);
    free(col_def_arr);
    return 0;
}

static int32_t CheckCreateTblReqIsValid(const LCSCreateTblReq *req)
{
    if (req == NULL) {
        LOG(ERROR) << "req is NULL";
        return EINVAL;
    }
    return 0;
}

int32_t IcebergToSQLCreateTblSQLNew(const LCSCreateTblReq *req, uint8_t **sql_buf)
{
    UNUSED_PARAM(create_tbl_req_tmpl_str);
    UNUSED_PARAM(sql_buf);
    int32_t ret = 0;
    ret = CheckCreateTblReqIsValid(req);
    if (ret != 0) {
        LOG(ERROR) << "check create table req failed";
        return ret;
    }

    int32_t target_config_str_len = snprintf(NULL, 0,
        iceberg_server_config_tmpl_str, req->connConfig.type,
        req->connConfig.warehouse_name);
    uint8_t *config_str = NULL;
    config_str = (uint8_t *)malloc((size_t)target_config_str_len + 1);
    if (config_str == NULL) {
        LOG(ERROR) << "alloc config_str failed";
        return ENOMEM;
    }
    ret = snprintf((char *)(config_str), (size_t)target_config_str_len + 1,
        iceberg_server_config_tmpl_str, req->connConfig.type,
        req->connConfig.warehouse_name);
    if (ret != target_config_str_len) {
        LOG(ERROR) << "generate config str failed";
        free(config_str);
        return EPIPE;
    }
    LOG(INFO) << "generate config str: " << config_str;

    int32_t target_sql_str_len = snprintf(NULL, 0, create_tbl_req_tmpl_str,
        req->ns_name,
        req->tbl_name,
        config_str,
        req->ns_name,
        req->tbl_name);
    *sql_buf = (uint8_t *)malloc((size_t)target_sql_str_len + 1);
    if (*sql_buf == NULL) {
        LOG(ERROR) << "alloc sql_buf failed";
        return ENOMEM;
    }
    ret = snprintf((char *)(*sql_buf), (size_t)target_sql_str_len + 1,
        create_tbl_req_tmpl_str,
        req->ns_name,
        req->tbl_name,
        config_str,
        req->ns_name,
        req->tbl_name);
    if (ret != target_sql_str_len) {
        LOG(ERROR) << "generate sql str failed";
        free(config_str);
        free(sql_buf);
        return EPIPE;
    }
    LOG(INFO) << "generate create tbl sql: " << (char *)(*sql_buf);
    free(config_str);
    return 0;
}

int32_t IcebergToSQLDelTblSQLNew(const LCSDelTblReq *req, uint8_t **sql_buf)
{
    int32_t ret = 0;
    int32_t target_str_len = snprintf(NULL, 0, del_tbl_req_tmpl_str, req->ns_name, req->tbl_name);
    *sql_buf = (uint8_t *)malloc((size_t)target_str_len + 1);
    if (*sql_buf == NULL) {
        LOG(ERROR) << "alloc sql_buf failed";
        return ENOMEM;
    }
    ret = snprintf((char *)(*sql_buf), (size_t)target_str_len + 1, del_tbl_req_tmpl_str,
        req->ns_name, req->tbl_name);
    if (ret != target_str_len) {
        LOG(ERROR) << "generate del sql str failed";
        free(*sql_buf);
        return EPIPE;
    }
    LOG(INFO) << "generate del tbl sql: " << (char *)(*sql_buf);
    return 0;
}

void IcebergToSQLFreeBuf(uint8_t **sql_buf)
{
    free(*sql_buf);
    *sql_buf = NULL;
    return;
}