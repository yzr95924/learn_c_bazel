/**
 * @file rest_server.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief implementation of a demo rest server
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "rest_server.h"

httplib::Server *g_rest_server_ptr;
constexpr const int kListenPort = 12345;

int32_t RestServerInit()
{
    g_rest_server_ptr = new httplib::Server();
    // g_rest_server_ptr->listen("localhost", kListenPort);

    LOG(INFO) << "init RestServer done, listen: " << kListenPort;
    return 0;
}

void RestServerDestroy()
{
    delete g_rest_server_ptr;
    LOG(INFO) << "destroy RestServer done";
}