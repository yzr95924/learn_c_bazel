load("@my_buildframe//:copts.bzl", "GLOBAL_DEFAULT_COPTS")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "rest_demo",
    srcs = [
        "rest_server.cc",
    ],
    hdrs = [
        "rest_server.h",
    ],
    includes = [
        ".",
    ],
    deps = [
        "@com_glog//:glog",
        "@com_cpp_httplib//:cpp-httplib",
        "//src/include:inner_include",
    ],
    copts = GLOBAL_DEFAULT_COPTS,
    linkopts = [],
)