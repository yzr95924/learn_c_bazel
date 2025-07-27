#include <stdio.h>

#include "pg_client.h"
#include "common_util.h"

static void InitGlog(const char *argv0) {
    google::InitGoogleLogging(argv0);
    FLAGS_logtostderr = true;
    FLAGS_colorlogtostderr = true;
};

static void ReleaseGlog()
{
    google::ShutdownGoogleLogging();
}

int main(int argc, char** argv) {
    UNUSED_PARAM(argc);

    InitGlog(argv[0]);
    PGClientDemo();
    ReleaseGlog();
    return 0;
}
