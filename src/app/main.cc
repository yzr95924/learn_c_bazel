#include <stdio.h>
#include "pg_client.h"

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    int32_t ret = 0;
    PGconn *conn = NULL;

    ret = PGClientInit(&conn);
    if (ret != 0) {
        return ret;
    } else {
        PGClientClose(&conn);
    }

    uint8_t *buf = (uint8_t *)malloc(32);
    memset(buf, 1, 1);
    buf = NULL;
    LOG(INFO) << "hello world: " << argc;
    google::ShutdownGoogleLogging();
    return 0;
}
