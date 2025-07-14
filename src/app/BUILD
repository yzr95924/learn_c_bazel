load("//buildframe:defs.bzl", "GLOBAL_COPTS")
load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "MQSim",
    srcs = [
        "main.cc"
    ],
    deps = [
        "@com_glog//:glog",
    ],
    copts = GLOBAL_COPTS,
)