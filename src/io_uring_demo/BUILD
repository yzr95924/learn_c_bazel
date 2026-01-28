load("@my_buildframe//:copts.bzl", "GLOBAL_DEFAULT_COPTS")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "io_uring_demo",
    srcs = glob([
        "*.cc",
    ]),
    hdrs = [
    ],
    includes = [
        ".",
    ],
    deps = [
        "@com_liburing//:liburing",
        "@com_glog//:glog",
        "//src/include:inner_include",
    ],
    copts = GLOBAL_DEFAULT_COPTS,
    linkopts = [],
)