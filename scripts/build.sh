#!/usr/bin/bash
# bazel clean --expunge
bazel build --config=debug @learn_c_bazel//src/... --explain=build.log --subcommands=pretty_print
# bazel run @hedron_compile_commands//:refresh_all -- --config=debug
bazel run //:refresh_compile_commands -- --config=debug
