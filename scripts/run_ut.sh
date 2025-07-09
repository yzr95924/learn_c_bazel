# bazel clean
bazel test --config=debug @learn_c_bazel//ut:main_test --test_output=all --explain=test.log --subcommands=pretty_print
