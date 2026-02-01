"""
default copts，参考grpc的配置
"""

DEFAULT_WARNING_FLAGS = [
    # 通用告警字段
    "-Wall",  # 常用的告警
    "-Wextra",  # 在-Wall上额外的告警信息
    "-Wpedantic",  # 严格遵循 C/C++ 标准，警告所有不符合标准的语法/写法
    "-Werror",  # 将告警当作error
    # 自定义告警
    "-Wuninitialized",  # 警告未初始化的变量使用
    "-Wnull-dereference",  # 警告空指针解引用的潜在风险
    "-Wconversion",  # 警告隐式类型转换（如int转char、double转int）
    "-Wsign-conversion",  # 专门警告有符号/无符号类型的隐式转换（如int转unsigned int）
    "-Wunused-variable",  # 警告定义但未使用的变量
    "-Wunused-function",  # 警告定义但未使用的函数
    "-Wunreachable-code",  # 警告不可达的代码
    "-Wformat",  # 检查格式化字符串错误
    "-Wformat-security",  # 专门警告格式化字符串安全问题
    "-Waddress-of-temporary",  # 警告对临时对象取地址
    "-Wdeprecated-declarations",  # 警告使用已标记为废弃
    "-Wc++20-extensions",  # c++20扩展
]

ASAN_COPTS = [
    "-fsanitize=address",  # 启用AddressSanitizer
    "-fsanitize=leak",  # 显式启用内存泄漏检测
    "-fsanitize-address-use-after-scope",  # 检测栈内存 “使用后超出作用域” 的问题
    "-g",  # 启用调试信息
    "-fno-omit-frame-pointer",  # 保留帧指针
    "-fno-optimize-sibling-calls",  # 禁用优化以便调试
]

ASAN_LINK_OPTS = [
    # "-lasan",
    "-fsanitize=address",
]

GLOBAL_DEFAULT_LINK_OPTS = select({
    "//:debug_mode": [
        "-g",
        "-O0",
        "-Wl,--export-dynamic",  # 导出所有动态符号，便于lldb/gdb调试
        "-Wl,--build-id=sha1",  # 生成唯一构建ID，方便定位调试符号文件
    ],
    "//:release_mode": [
        "-Wl,--strip-debug",  # 仅剥离调试符号（保留基础符号，推荐）
    ],
    "//conditions:default": [
        "-Wl,-z,relro,-z,now",  # 保留基础安全选项
    ],
}) + select({
    "//:use_termux": ["-llog"],
    "//conditions:default": [],
}) + select({
    "//:use_asan": ASAN_LINK_OPTS,
    "//conditions:default": [],
}) + [
    "-Wl,-Bsymbolic",
    "-fPIC",
]

GLOBAL_DEFAULT_COPTS = DEFAULT_WARNING_FLAGS + select({
    "//:debug_mode": ["-g", "-O0"],
    "//:release_mode": ["-O3", "-DNDEBUG", "-D_MY_DEBUG"],
    "//conditions:default": [],
}) + select({
    "@platforms//os:linux": ["-D_LINUX"],
    "@platforms//os:windows": ["-D_WINDOWS"],
    "//conditions:default": [],
}) + select({
    "//:use_asan": ASAN_COPTS,
    "//conditions:default": [],
}) + [
    "-std=c++17",
    "-fPIC",
]
