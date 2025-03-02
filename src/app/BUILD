cc_binary(
    name = "MQSim",
    srcs = [
        "main.cc"
    ],
    deps = [
        "@com_github_glog//:glog"
    ],
)

load("@com_grail_bazel_compdb//:defs.bzl", "compilation_database")
load("@com_grail_bazel_output_base_util//:defs.bzl", "OUTPUT_BASE")
compilation_database(
    name = "compile_db",
    targets = [
        "//src/app:MQSim",
    ],
    # OUTPUT_BASE is a dynamic value that will vary for each user workspace.
    # If you would like your build outputs to be the same across users, then
    # skip supplying this value, and substitute the default constant value
    # "__OUTPUT_BASE__" through an external tool like `sed` or `jq` (see
    # below shell commands for usage).
    output_base = OUTPUT_BASE,
)