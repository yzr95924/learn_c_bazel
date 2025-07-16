"""
default copts，参考grpc的配置
"""


DEFAULT_WARNING_FLAGS = [
    # Enable all & extra warnings
    "-Wall",
    "-Wextra",
    # Avoid some known traps
    "-Wimplicit-fallthrough",
    # Consider warnings as errors
    "-Werror",
    # Ignore unknown warning flags
    "-Wno-unknown-warning-option",
    # A list of enabled flags coming from internal build system
    "-Wc++20-extensions",
    "-Wctad-maybe-unsupported",
    "-Wdeprecated-increment-bool",
    "-Wfloat-overflow-conversion",
    "-Wfloat-zero-conversion",
    "-Wfor-loop-analysis",
    "-Wformat-security",
    "-Wgnu-redeclared-enum",
    "-Winfinite-recursion",
    "-Wliteral-conversion",
    "-Wnon-virtual-dtor",
    "-Woverloaded-virtual",
    "-Wself-assign",
    "-Wstring-conversion",
    "-Wtautological-overlap-compare",
    "-Wthread-safety-analysis",
    "-Wthread-safety-beta",
    "-Wunused-but-set-variable",
    "-Wunused-comparison",
    "-Wvla",
    # -Wextra compatibility between gcc and clang
    "-Wtype-limits",
    # A list of disabled flags coming from internal build system
    "-Wno-string-concatenation",
    # Exceptions but will be removed
    "-Wno-deprecated-declarations",
    "-Wno-unused-function",
    "-Wno-unused-value", # 保留显式禁用
]

ASAN_COPTS = [
    "-fsanitize=address",  # 启用 AddressSanitizer
    "-g",                   # 启用调试信息
    "-fno-omit-frame-pointer",  # 保留帧指针
    "-fno-optimize-sibling-calls",  # 禁用优化以便调试
]

ASAN_LINK_OPTS = [
    "-lasan",
]

GLOBAL_LINK_OPTS = select({
    "//:debug_mode": ["-g"],
    "//:release_mode": [],
    "//conditions:default": [],
}) + select({
    "//:use_asan": ASAN_LINK_OPTS,
    "//conditions:default": [],
})

GLOBAL_DEFAULT_COPTS = DEFAULT_WARNING_FLAGS + select({
    "//:use_asan": ASAN_COPTS,
    "//conditions:default": [],
}) + select({
    "//:debug_mode": ["-g", "-O0"],
    "//:release_mode": ["-O3"],
    "//conditions:default": [],
})
