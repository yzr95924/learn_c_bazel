#!/usr/bin/bash
# bazel clean --expunge
bazel build --compilation_mode=dbg --config=debug @yzr95924_MQSim_bazel//src/app:MQSim --explain=build.log --subcommands=pretty_print
bazel run @hedron_compile_commands//:refresh_all -- --config=debug
