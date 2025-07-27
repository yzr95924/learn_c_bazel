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

static int32_t InitPGClient(PGconn **retConn)
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

static int32_t CreatePGTable(PGconn *conn)
{
    int32_t ret = 0;
    if (PQstatus(conn) != CONNECTION_OK) {
        LOG(ERROR) << "pg connection failed";
        return ECONNREFUSED;
    }
    const char *createTblSQL =
        "CREATE TABLE IF NOT EXISTS employees ("
        "   id SERIAL PRIMARY KEY,"
        "   name VARCHAR(100) NOT NULL,"
        "   age INT,"
        "   salary REAL"
        ");";
    LOG(INFO) << "run sql: \n" << createTblSQL;
    PGresult *res = PQexec(conn, createTblSQL);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        LOG(ERROR) << "create table failed";
        ret = EIO;
    }
    PQclear(res);
    return ret;
}

static void ClosePGClient(PGconn **conn)
{
    if (*conn != NULL) {
        PQfinish(*conn);
        *conn = NULL;
    }
    LOG(INFO) << "close PG connection done";
    return;
}

void PGClientDemo()
{
    int32_t ret = 0;
    PGconn *conn = NULL;
    LOG(INFO) << "start to run pg client demo";

    do {
        ret = InitPGClient(&conn);
        if (ret != 0) {
            LOG(ERROR) << "pg client init failed, ret: " << ret;
            break;
        }

        ret = CreatePGTable(conn);
        if (ret != 0) {
            LOG(ERROR) << "pg client create table failed, ret: " << ret;
            break;
        }
    } while (0);

    ClosePGClient(&conn);
    return;
}