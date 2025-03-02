#!/usr/bin/bash
# Command to generate the compilation database file.
bazel build //src/app:compile_db --config=debug

# Location of the compilation database file.
outfile="$(bazel info bazel-bin)/src/app/compile_commands.json"
link_cur_dir="$(bazel info execution_root)"
real_cur_dir="$(pwd)"

# replace
sed -i "s@${link_cur_dir}@${real_cur_dir}@g" ${outfile}

result="$(bazel info workspace)/compile_commands.json"
mv ${outfile} ${result}

# The compilation database is now ready to use at this location.
echo "Compilation Database: ${result}"