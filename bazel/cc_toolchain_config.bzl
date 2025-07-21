"""
自定义c/c++ tool chain
"""

load("@rules_cc//cc/common:cc_common.bzl", "cc_common")
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")
load("@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl", "tool_path", "feature", "flag_group", "flag_set")

all_link_actions = [
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

def _impl(ctx):
    tool_paths = [
        tool_path(name = "gcc", path = "/usr/bin/clang"),           # C/C++ 编译器（必须）
        tool_path(name = "ld", path = "/usr/bin/ld"),               # 链接器（必须）
        tool_path(name = "ar", path = "/usr/bin/ar"),               # 静态库归档工具
        tool_path(name = "cpp", path = "/usr/bin/cpp"),             # C 预处理器
        tool_path(name = "gcov", path = "/usr/bin/gcov"),           # 代码覆盖率工具
        tool_path(name = "nm", path = "/usr/bin/nm"),               # 符号查看器
        tool_path(name = "objdump", path = "/usr/bin/objdump"),     # 目标文件分析工具
        tool_path(name = "strip", path = "/usr/bin/strip"),         # 去除调试符号工具
    ]

    features = [
        feature(
            name = "default_linker_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_link_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-lstdc++",
                            ],
                        ),
                    ]),
                ),
            ],
        ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,
        cxx_builtin_include_directories = [
            # 使用命令 echo | clang++ -x c++ -E -v - 2>&1 | grep "^ /" 或者 "gcc -E -xc++ - -v"
            # 系统头文件
            "/usr/include",
            "/usr/include/x86_64-linux-gnu",
            "/usr/local/include",
            # clang 运行时头文件
            "/usr/lib/llvm-18/lib/clang/18/include",
            # Asan
            "/usr/lib/llvm-18/lib/clang/18/share",
            # c/c++标准库
            "/usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13",
            "/usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/x86_64-linux-gnu/c++/13",
            "/usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/backward",
        ],
        toolchain_identifier = "my_cc_x86_64-toolchain",
        host_system_name = "linux",
        target_system_name = "linux",
        target_cpu = "x86_64",
        target_libc = "unknown",
        compiler = "clang",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,
    )

my_cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)