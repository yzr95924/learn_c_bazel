/**
 * @file common_util.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief common util header
 * @version 0.1
 * @date 2025-07-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LEARN_C_BAZEL_COMMON_UTIL
#define LEARN_C_BAZEL_COMMON_UTIL

#include <bits/stdc++.h>
#include <error.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

// common use header
#include "glog/logging.h"

#ifndef UNUSED_PARAM(x)
#define UNUSED_PARAM(x) (void)(x)
#endif

#ifndef RETURN_INNER_OK
#define RETURN_INNER_OK (0)
#endif

#ifndef RETURN_INNER_ERR
#define RETURN_INNER_ERR (-1)
#endif

#define MAX_NS_NAME_LEN 64
#define MAX_TBL_NAME_LEN 64

#endif
