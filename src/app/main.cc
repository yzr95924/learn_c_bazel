#include <stdio.h>

#include "pg_client.h"
#include "common_util.h"
#include "linux_os_util.h"

static void InitGlog(const char *argv0)
{
    google::InitGoogleLogging(argv0);
    FLAGS_logtostderr = true;
    FLAGS_colorlogtostderr = true;
};

static void ReleaseGlog()
{
    google::ShutdownGoogleLogging();
}

int main(int argc, char **argv)
{
    UNUSED_PARAM(argc);

    InitGlog(argv[0]);
    ReleaseGlog();

    int32_t instance_fd = 0;
    int32_t watch_fd = 0;
    pthread_t watch_thd_id = 0;
    int32_t ret = LinuxOSUtilRegNotifyFile("/tmp/test", &instance_fd, &watch_fd, &watch_thd_id);
    if (ret != RETURN_INNER_OK) {
        return -1;
    }
    pthread_join(watch_thd_id, NULL);
    LOG(INFO) << "event thread done";
    LinuxOSUtilUnRegNotifyFile(instance_fd, watch_fd);
    return 0;
}
