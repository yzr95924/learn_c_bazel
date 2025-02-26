#!/usr/bin/bash
bazel clean --expunge
bazel build --config=debug --config=asan //src/app:MQSim --explain=build.log --subcommands=pretty_print
