/**
 * @file 460_lfu_cache.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief 460. LFU 缓存 https://leetcode.cn/problems/lfu-cache/description/
 * @version 0.1
 * @date 2026-02-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "leetcode_app.h"

typedef struct {
} LFUCache;

LFUCache *lFUCacheCreate(int capacity)
{
    UNUSED_PARAM(capacity);
    return NULL;
}

int lFUCacheGet(LFUCache *obj, int key)
{
    UNUSED_PARAM(obj);
    UNUSED_PARAM(key);
    return 0;
}

void lFUCachePut(LFUCache *obj, int key, int value)
{
    UNUSED_PARAM(obj);
    UNUSED_PARAM(key);
    UNUSED_PARAM(value);
    return;
}

void lFUCacheFree(LFUCache *obj)
{
    UNUSED_PARAM(obj);
    return;
}

/**
 * Your LFUCache struct will be instantiated and called as such:
 * LFUCache* obj = lFUCacheCreate(capacity);
 * int param_1 = lFUCacheGet(obj, key);

 * lFUCachePut(obj, key, value);

 * lFUCacheFree(obj);
*/