# bazel clean
bazel test --compilation_mode=dbg \
	--define=use_termux=true \
	@learn_c_bazel//ut/... \
	--test_output=all \
	--explain=test.log \
	--subcommands=pretty_print

python3 ./scripts/generate_compile_commands.py \
	-t //ut/... \
	-o \"--compilation_mode=dbg\"
