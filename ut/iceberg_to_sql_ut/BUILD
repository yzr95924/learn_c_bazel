load("@my_buildframe//:copts.bzl", "GLOBAL_DEFAULT_COPTS")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "iceberg_to_sql_ut",
    srcs = [
        "iceberg_to_sql_ut.cc",
    ],
    data = [
        "//data:test_data",
    ],
    deps = [
        "@com_googletest//:gtest",
        "//src/iceberg_to_sql:iceberg_to_sql",
    ],
    copts = GLOBAL_DEFAULT_COPTS,
)