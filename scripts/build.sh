#!/usr/bin/bash
bazel clean
bazel build --compilation_mode=dbg --define=use_asan=true @learn_c_bazel//src/... --platforms=@learn_c_bazel//:linux_x86_64 --explain=build.log --subcommands=pretty_print
# bazel run @hedron_compile_commands//:refresh_all -- --config=debug
#bazel run //:refresh_compile_commands -- --compilation_mode=dbg
