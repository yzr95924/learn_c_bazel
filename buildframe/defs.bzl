"""
定义工程内通用的变量
"""

GLOBAL_COPTS = select({
    "//:debug_mode": ["-O0", "-g", "-fno-omit-frame-pointer", "-Wl,-Bsymbolic"],
    "//:release_mode": ["-O3"],
    "//conditions:default": [],
}) + [
    "-std=c++17",
    "-Wall",
    "-Werror",
    "-Wextra",
    "-Wformat=2",       # 合并多个格式相关警告
    "-Wcast-align",
    "-Wno-unused-value", # 保留显式禁用
    "-Wwrite-strings",
]

GLOBAL_LINK_OPTS = select({
    "//:debug_mode": ["-Wl,--no-strip", "-g"],
    "//:release_mode": [],
    "//conditions:default": [],
})