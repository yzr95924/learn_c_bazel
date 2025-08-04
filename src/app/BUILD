load("@my_buildframe//:copts.bzl", "GLOBAL_DEFAULT_COPTS", "GLOBAL_LINK_OPTS")
load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "MQSim",
    srcs = [
        "main.cc"
    ],
    deps = [
        "//src/pg_client:pg_client",
        "//src/rest_demo:rest_demo"
    ],
    copts = GLOBAL_DEFAULT_COPTS,
    linkopts = GLOBAL_LINK_OPTS,
    linkstatic = True,
)
