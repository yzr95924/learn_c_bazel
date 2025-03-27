bazel clean
bazel test --config=debug @yzr95924_MQSim_bazel//ut:main_test --test_output=all --explain=test.log --subcommands=pretty_print