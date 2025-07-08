#include <stdio.h>
#include "glog/logging.h"
#include "third_part_lib/my_module.h"

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;

    uint8_t *buf = (uint8_t *)malloc(1);
    LOG(INFO) << "hello world";
    google::ShutdownGoogleLogging();
    MyModuleTest();
    return 0;
}
