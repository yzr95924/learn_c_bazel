#!/usr/bin/bash
bazel clean
bazel build //src/app:MQSim --explain=build.log --subcommands=pretty_print