#!/usr/bin/bash
bazel build --compilation_mode=dbg --config=debug --config=termux @yzr95924_MQSim_bazel//src/app:MQSim --explain=build.log --subcommands=pretty_print

old_python_path="$(bazel info execution_root)/bazel-out/aarch64-fastbuild/bin/external/hedron_compile_commands~/refresh_all.runfiles/rules_python~~python~python_3_11_aarch64-unknown-linux-gnu/bin/python3"
current_python_path="$(which python3)"
rm $old_python_path
ln -s $current_python_path $old_python_path

bazel run @hedron_compile_commands//:refresh_all -- --config=termux
