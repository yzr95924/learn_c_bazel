#!/usr/bin/bash
bazel build --compilation_mode=dbg --config=debug --config=termux @yzr95924_MQSim_bazel//src/app:MQSim --explain=build.log --subcommands=pretty_print
bazel run @hedron_compile_commands//:refresh_all  -- --compilation_mode=dbg -- --config=debug -- --config=termux