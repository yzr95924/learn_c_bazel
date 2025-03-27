#!/usr/bin/bash
bazel build --config=debug --config=termux @yzr95924_MQSim_bazel//src/app:MQSim --explain=build.log --subcommands=pretty_print

old_python_path="$(bazel info execution_root)/bazel-out/aarch64-fastbuild/bin/refresh_compile_commands.runfiles/rules_python~~python~python_3_11_aarch64-unknown-linux-gnu/bin/python3"
current_python_path="$(which python3)"

if [ ! -f $old_python_path ]; then
    bazel run //:refresh_compile_commands -- --config=termux
fi

set -x
rm $old_python_path
ln -s $current_python_path $old_python_path
set +x
bazel run //:refresh_compile_commands -- --config=termux
