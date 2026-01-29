load("@my_buildframe//:copts.bzl", "GLOBAL_DEFAULT_COPTS", "GLOBAL_LINK_OPTS")
load("@rules_cc//cc:cc_test.bzl", "cc_test")
package(default_visibility = ["//visibility:public"])

cc_test(
    name = "ut_main",
    deps = [
        "//ut/iceberg_to_sql_ut:iceberg_to_sql_ut",
        "@com_googletest//:gtest_main", # for gtest main entry
    ],
    size = "small",
    copts = GLOBAL_DEFAULT_COPTS,
    linkopts = GLOBAL_LINK_OPTS
)