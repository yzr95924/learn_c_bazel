load("@my_buildframe//:copts.bzl", "GLOBAL_DEFAULT_COPTS", "GLOBAL_LINK_OPTS")
load("@rules_cc//cc:cc_test.bzl", "cc_test")
package(default_visibility = ["//visibility:public"])

cc_test(
    name = "ut_main",
    deps = [
        "@com_googletest//:gtest_main", # for gtest main entry
        "//ut/rest_server_ut:rest_demo_ut",
    ],
    size = "small",
    copts = GLOBAL_DEFAULT_COPTS,
    linkopts = GLOBAL_LINK_OPTS
)