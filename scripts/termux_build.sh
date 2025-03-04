#!/usr/bin/bash
bazel build --config=debug --config=termux @yzr95924_MQSim_bazel//src/app:MQSim --explain=build.log --subcommands=pretty_print
bazel run @hedron_compile_commands//:refresh_all  -- --config=debug -- --config=termux
