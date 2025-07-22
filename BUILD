load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

refresh_compile_commands(
    name = "refresh_compile_commands",

    # Specify the targets of interest.
    # For example, specify a dict of targets and any flags required to build.
    targets = {
      "//src/app:all": "",
      "//ut:main_test": "",
    },
    # No need to add flags already in .bazelrc. They're automatically picked up.
    # If you don't need flags, a list of targets is also okay, as is a single target string.
    # Wildcard patterns, like //... for everything, *are* allowed here, just like a build.
      # As are additional targets (+) and subtractions (-), like in bazel query https://docs.bazel.build/versions/main/query.html#expressions
    # And if you're working on a header-only library, specify a test or binary target that compiles it.
)

config_setting(
    name = "debug_mode",
    values = {
        "compilation_mode": "dbg",
    }
)

config_setting(
    name = "release_mode",
    values = {
        "compilation_mode": "opt",
    }
)

# switch of using asan
config_setting(
    name = "use_asan",
    values = {
        "define": "use_asan=true",
    }
)

# switch of using termux
config_setting(
    name = "use_termux",
    values = {
        "define": "use_termux=true",
    }
)

platform(
    name = "linux_x86_64",
    constraint_values = [
        "@platforms//os:linux",
        "@platforms//cpu:x86_64",
    ]
)
