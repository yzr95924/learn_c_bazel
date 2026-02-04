/**
 * @file linux_os_util.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief linux os util interface
 * @version 0.1
 * @date 2026-02-01
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef LINUX_OS_UTIL_H
#define LINUX_OS_UTIL_H

#include "common_util.h"
#include "pthread.h"

/**
 * @brief reg a file to the inotify instance
 *
 * @param[in] file_path file path
 * @param[out] instance_fd ret inotify instance fd
 * @param[out] watch_fd ret watch file fd
 * @param[out] watch_thd_id ret watch thread id
 * @return int32_t inner err code
 */
int32_t LinuxOSUtilRegNotifyFile(const char *file_path, int32_t *instance_fd, int32_t *watch_fd,
                                 pthread_t *watch_thd_id);

/**
 * @brief unreg a file to the inotify instance
 *
 * @param[in] instance_fd instance fd
 * @param[out] watch_fd watch file fd
 */
void LinuxOSUtilUnRegNotifyFile(int32_t instance_fd, int32_t watch_fd);

#endif // LINUX_OS_UTIL_H
