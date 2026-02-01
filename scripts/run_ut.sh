# bazel clean
bazel build --compilation_mode=dbg \
    --define=use_asan=true \
	@learn_c_bazel//ut:ut_main \
	--test_output=all \
	--explain=test.log \
	--subcommands=pretty_print

# python3 ./scripts/generate_compile_commands.py \
    # -o \"--compilation_mode=dbg\" \
    # -t //ut:ut_main
