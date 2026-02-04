/**
 * @file inotify_test.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief test inotify util
 * @version 0.1
 * @date 2026-02-01
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <sys/inotify.h>

#include "linux_os_util.h"

#define EVENT_BUF_LEN 1024

typedef struct {
    int32_t instance_fd;
    int32_t watch_fd;
} WatcherThdArgs;

static WatcherThdArgs g_thd_args = {0, 0};

void *WatchThread(void *watch_thd_args)
{
    WatcherThdArgs *args = (WatcherThdArgs *)watch_thd_args;
    LOG(INFO) << "create watch thread for instance_fd: " << args->instance_fd << ", "
              << "watch_fd: " << args->watch_fd;

    uint8_t buf[EVENT_BUF_LEN] = {0};

    // block until event happen
    ssize_t len = read(args->instance_fd, buf, EVENT_BUF_LEN);
    if (len < 0) {
        LOG(ERROR) << "failed to read, len: " << len;
        return NULL;
    }
    LOG(INFO) << "receive inotfy read, len: " << len;
    for (uint8_t *ptr = buf; ptr < buf + len;) {
        struct inotify_event *event = (struct inotify_event *)ptr;
        if (event->mask & IN_DELETE) {
            LOG(INFO) << "get delete event";
        }
        if (event->mask & IN_DELETE_SELF) {
            LOG(INFO) << "get delete-self event";
        }
        ptr += sizeof(struct inotify_event) + event->len;
    }

    return NULL;
}

int32_t LinuxOSUtilRegNotifyFile(const char *file_path, int32_t *instance_fd, int32_t *watch_fd,
                                 pthread_t *watch_thd_id)
{
    int32_t tmp_instance_fd = 0;
    int32_t tmp_watch_fd = 0;
    int32_t ret = RETURN_INNER_OK;
    pthread_t tmp_watch_thd_id = 0;

    do {
        // create inotify instance
        tmp_instance_fd = inotify_init();
        if (tmp_instance_fd < 0) {
            LOG(ERROR) << "init inotify instance failed, ret: " << tmp_instance_fd;
            ret = RETURN_INNER_ERR;
            break;
        }
        LOG(INFO) << "init inotify instance done, tmp_instance_fd: " << tmp_instance_fd;

        // add watch file to the inotify instance
        tmp_watch_fd = inotify_add_watch(tmp_instance_fd, file_path, IN_MODIFY | IN_CREATE | IN_DELETE);
        if (tmp_watch_fd < 0) {
            LOG(ERROR) << "add watch file failed, file_path: " << file_path << ", ret: " << tmp_watch_fd << ", "
                       << "errno: " << errno;
            close(tmp_instance_fd);
            ret = RETURN_INNER_ERR;
            break;
        }
        LOG(INFO) << "add watch done, tmp_watch_id: " << tmp_watch_fd;

        g_thd_args.instance_fd = tmp_instance_fd;
        g_thd_args.watch_fd = tmp_watch_fd;
        if (pthread_create(&tmp_watch_thd_id, NULL, WatchThread, &g_thd_args) != 0) {
            LOG(ERROR) << "create watch thread failed";
            inotify_rm_watch(tmp_instance_fd, tmp_watch_fd);
            close(tmp_instance_fd);
            ret = RETURN_INNER_ERR;
            break;
        }
        *instance_fd = tmp_instance_fd;
        *watch_fd = tmp_watch_fd;
        *watch_thd_id = tmp_watch_thd_id;
    } while (0);

    return ret;
}

void LinuxOSUtilUnRegNotifyFile(int32_t instance_fd, int32_t watch_fd)
{
    inotify_rm_watch(instance_fd, watch_fd);
    close(instance_fd);
    return;
}
