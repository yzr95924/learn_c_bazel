load("@my_buildframe//:copts.bzl", "GLOBAL_DEFAULT_COPTS", "GLOBAL_LINK_OPTS")
load("@rules_cc//cc:cc_test.bzl", "cc_test")
package(default_visibility = ["//visibility:public"])

cc_test(
    name = "rest_demo_ut",
    srcs = [
        "rest_server_ut.cc",
    ],
    deps = [
        "@com_googletest//:gtest",
        "@com_googletest//:gtest_main",
        "@learn_c_bazel//src/rest_demo:rest_demo",
    ],
    size = "small",
    copts = GLOBAL_DEFAULT_COPTS,
    linkopts = GLOBAL_LINK_OPTS
)