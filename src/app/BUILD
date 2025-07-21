load("@my_buildframe//:copts.bzl", "GLOBAL_DEFAULT_COPTS", "GLOBAL_LINK_OPTS")
load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "MQSim",
    srcs = [
        "main.cc"
    ],
    deps = [
        "@com_glog//:glog",
        "@com_postgres//:libpq",
    ],
    copts = GLOBAL_DEFAULT_COPTS,
    linkopts = GLOBAL_LINK_OPTS,
    linkstatic = True,
)