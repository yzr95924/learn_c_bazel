#!/usr/bin/bash
# bazel clean --expunge
bazel clean
bazel build --config=debug --config=termux @yzr95924_MQSim_bazel//src/app:MQSim --explain=build.log --subcommands=pretty_print
