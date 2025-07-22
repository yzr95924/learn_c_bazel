#!/usr/bin/bash
bazel clean
bazel build --compilation_mode=dbg \
    --define=use_asan=true \
    @learn_c_bazel//src/app:MQSim \
    --explain=build.log \
    --subcommands=pretty_print \
    --verbose_failures
bazel run //:refresh_compile_commands -- --compilation_mode=dbg
