#include <stdio.h>
#include "glog/logging.h"
#include "libpq-fe.h"

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;

    uint8_t *buf = (uint8_t *)malloc(32);
    uint8_t *buf_8 = (uint8_t *)malloc(32);
    memset(buf, 1, 1);
    memset(buf_8, 1, 1);
    buf = NULL;
    buf_8 = NULL;
    LOG(INFO) << "hello world: " << argc;
    google::ShutdownGoogleLogging();
    return 0;
}
