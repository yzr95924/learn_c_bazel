#include <stdio.h>
#include "glog/logging.h"

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;

    uint8_t *buf = (uint8_t *)malloc(1);
    free(buf);
    LOG(INFO) << "hello world: " << argc;
    google::ShutdownGoogleLogging();
    return 0;
}
