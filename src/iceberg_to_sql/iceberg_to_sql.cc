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


int32_t IcebergToSQLCreateTblSQL(const LCSCreateTblReq *req, uint8_t **sql_buf)
{
    UNUSED_PARAM(sql_buf)
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
    }

    return 0;
}

void IcebergToSQLFreeBuf(uint8_t **sql_buf)
{
    UNUSED_PARAM(sql_buf)
    return;
}