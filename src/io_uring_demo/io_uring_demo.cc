/**
 * @file io_uring_demo.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief A demo of using io_uring
 * @version 0.1
 * @date 2025-12-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "io_uring_demo.h"

int32_t io_uring_demo_run()
{
    int32_t ret = 0;
    struct io_uring ring;
    ret = io_uring_queue_init(32, &ring, 0);
    if (ret != 0) {
        LOG(ERROR) << "io_uring_queue_init failed, ret=" << ret;
        return ret;
    }
    return 0;
}