load("@my_buildframe//:copts.bzl", "GLOBAL_DEFAULT_COPTS")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "rest_demo_ut",
    srcs = [
        "rest_server_ut.cc",
    ],
    deps = [
        "@com_googletest//:gtest",
        "@learn_c_bazel//src/rest_demo:rest_demo",
    ],
    copts = GLOBAL_DEFAULT_COPTS,
)