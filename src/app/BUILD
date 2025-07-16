load("@my_buildframe//:copts.bzl", "GLOBAL_DEFAULT_COPTS", "GLOBAL_LINK_OPTS")
load("@my_buildframe//:defs.bzl", "debug_print_var")
load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "MQSim",
    srcs = [
        "main.cc"
    ],
    deps = [
        "@com_glog//:glog",
    ],
    copts = GLOBAL_DEFAULT_COPTS,
    linkopts = GLOBAL_LINK_OPTS
)

debug_print_var("GLOBAL_LINK_OPTS", GLOBAL_LINK_OPTS)