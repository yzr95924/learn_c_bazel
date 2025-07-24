/**
 * @file pg_client.cc
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief pg client demo interface implementation
 * @version 0.1
 * @date 2025-07-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "pg_client.h"
#include <errno.h>

int32_t PGClientInit(PGconn **retConn)
{
    *retConn = NULL;
    *retConn = PQsetdbLogin(
        "192.168.100.210",
        "5432",
        NULL,
        NULL,
        "my_db",
        "admin",
        "pgadmin"
    );

    if (PQstatus(*retConn) != CONNECTION_OK) {
        LOG(ERROR) << "PQ connect failed";
        return EFAULT;
    }
    LOG(INFO) << "PG connection done";
    return 0;
}

void PGClientClose(PGconn **conn)
{
    PQfinish(*conn);
    *conn = NULL;
    LOG(INFO) << "close PG connection done";
    return;
}