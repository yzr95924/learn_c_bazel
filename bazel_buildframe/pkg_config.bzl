"""
use pkg-config to find libraries in the system
"""

load("@bazel_buildframe//:tool.bzl", "path", "which")

_DEFAULT_TEMPLATE = Label("@bazel_buildframe//:pkg_config.BUILD.tpl")

_DEFAULT_STATIC = False

def _run_pkg_config(repository_ctx, command_line, pkg_config_paths):
    """Run pkg-config command and return its tokenized output.

    Run command_line with PKG_CONFIG_PATH = pkg_config_paths and return its
    tokenized output.
    """
    pkg_config_path = ":".join(pkg_config_paths)
    print("[MY_DEBUG]: run pkg-config cmd: {}".format(command_line))
    result = repository_ctx.execute(
        command_line,
        environment = {
            "PKG_CONFIG_PATH": pkg_config_path,
        },
    )
    if result.return_code != 0:
        return struct(error = "error {} from {}: {}{}".format(
            result.return_code,
            command_line,
            result.stdout,
            result.stderr,
        ))
    tokens = [x for x in result.stdout.strip().split(" ") if x]
    return struct(tokens = tokens, error = None)

def _maybe_setup_pkg_config_repository(repository_ctx):
    """Sets up pkg-config repository configuration.

    This is the macro form of the pkg_config_repository() rule below.
    Refer to that rule's API documentation for details.

    This flavor of this rule is intended to be called by other repository_rule
    implementation functions.  The pkg_config_repository flavor of this rule is
    intended to be called directly from the WORKSPACE file, or from a macro
    that was called by the WORKSPACE file.
    """

    # First locate pkg-config.
    tool_path = which(repository_ctx, "pkg-config")
    if not tool_path:
        return struct(error = "Could not find pkg-config on PATH={}".format(
            path(repository_ctx),
        ))
    args = [tool_path, repository_ctx.attr.modname]

    # Grab any extra paths requested by the user.
    pkg_config_paths = list(getattr(
        repository_ctx.attr,
        "pkg_config_paths",
        [],
    ))

    # Convert the canonical name (e.g., "+_repo_rules+eigen") to its apparent
    # name (e.g., "eigen") so that when a BUILD file uses a label which omits
    # the target name (e.g., deps = ["@eigen"]) the unabbreviated label (e.g.,
    # "@eigen//:eigen") will match what we provide here.
    library_name = repository_ctx.name.split("+")[-1]

    # Check if we can find the required *.pc file of any version.
    result = _run_pkg_config(repository_ctx, args, pkg_config_paths)
    if result.error != None:
        return result

    # If we have a minimum version, enforce that.
    atleast_version = getattr(repository_ctx.attr, "atleast_version", "")
    if atleast_version:
        result = _run_pkg_config(repository_ctx, args + [
            "--atleast-version",
            atleast_version,
        ], pkg_config_paths)
        if result.error != None:
            return struct(error = result.error + "during version check")

    # Determine linkopts.
    static = getattr(repository_ctx.attr, "static", _DEFAULT_STATIC)
    libs_args = args + ["--libs"]
    if static:
        libs_args = libs_args + ["--static"]
    result = _run_pkg_config(repository_ctx, libs_args, pkg_config_paths)
    if result.error != None:
        return result
    linkopts = result.tokens

    # Bazel "linkopts=" must be either switches ("-foo"), variables ("$(FOO)"),
    # or labels ("foo").  We should only get switches from `pkg-config --libs`.
    # However, sometimes it produces "-framework CoreFoundation" or similar,
    # which is *supposed* to be a single switch, but our split heuristic
    # chopped it up.  We recombine non-switch args with their preceding arg as
    # a repair.  We process args in reverse order to keep our loop index
    # unchanged by a pop.
    for i in reversed(range(len(linkopts))):
        linkopt = linkopts[i]

        # Absolute system paths to *.dylib and *.so files get turned into -l
        # instead.
        if linkopt.endswith(".dylib") or linkopt.endswith(".so"):
            if linkopt.endswith(".dylib"):
                possible_libdirs = [
                    "/usr/lib",
                    "/usr/local/lib",
                ]
                suffix = ".dylib"
            elif linkopt.endswith(".so"):
                possible_libdirs = [
                    "/usr/lib",
                    "/usr/lib/x86_64-linux-gnu",
                ]
                suffix = ".so"
            else:
                return struct(error = ("expected linkopt {} to end with " +
                                       ".dylib or .so").format(linkopt))
            for dir in possible_libdirs:
                prefix = dir + "/lib"
                if linkopt.startswith(prefix):
                    name = linkopt[len(prefix):-len(suffix)]
                    if "/" not in name:
                        linkopt = "-l" + name
                        linkopts[i] = linkopt
                        break

        # Add `-Wl,-rpath,<path>` for `-L<path>`.
        # See https://github.com/RobotLocomotion/drake/issues/7387#issuecomment-359952616  # noqa
        if linkopt.startswith("-L"):
            linkopts.insert(i, "-Wl,-rpath," + linkopt[2:])
            continue

        # Switches stay put.
        if linkopt.startswith("-"):
            continue

        # A non-switch arg should be recombined with the preceding arg.
        non_switch_arg = linkopts.pop(i)
        if i == 0:
            return struct(error = "malformed linkopts: " + repr(linkopts))
        linkopts[i - 1] += " " + non_switch_arg
    print("[MY_DEBUG]: find linkopts({}) for {}".format(linkopts, library_name))

    # Determine cflags; we'll split into includes and defines in a moment.
    result = _run_pkg_config(
        repository_ctx,
        args + ["--cflags"],
        pkg_config_paths,
    )
    if result.error != None:
        return result
    cflags = result.tokens

    # Split cflags into includes and defines.  The -I paths from pkg-config
    # will be absolute paths; we'll make them relative in a moment.
    absolute_includes = []
    defines = []
    unknown_cflags = []

    # Blacklist various system include paths on macOS.
    blacklisted_includes = [
        "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include",  # noqa
        "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.0.sdk/usr/include",  # noqa
        "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.0.sdk/usr/include",  # noqa
        "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include",  # noqa
        "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include",
        "/Library/Developer/CommandLineTools/SDKs/MacOSX11.0.sdk/usr/include",
        "/Library/Developer/CommandLineTools/SDKs/MacOSX12.0.sdk/usr/include",
        "/Library/Developer/CommandLineTools/usr/include",
    ]

    # We process in reserve order to keep our loop index unchanged by a pop.
    for cflag in cflags:
        if cflag.startswith("-I"):
            value = cflag[2:]
            if value in blacklisted_includes:
                continue
            if value not in absolute_includes:
                absolute_includes.append(value)
        elif cflag.startswith("-D"):
            value = cflag[2:]
            if value not in defines:
                defines.append(value)
        elif cflag == "-pthread":
            # The pkg-config output has told us to use -pthread when compiling.
            # When compiling the typical effect of -pthread is to -D_REENTRANT;
            # when linking the typical effect of -pthread is to -lpthread.  In
            # Bazel, we can't pass -pthread in a cc_library's defines (it's not
            # a preprocessor definition), and we shouldn't pass -pthread only
            # in a cc_library's copts (i.e., non-transitively), since
            # respecting transitivity might be important for some toolchains.
            # Instead, when compiling our code that uses this library, we'll
            # decide to just ignore pkg-config's advice to use -pthread when
            # compiling and instead apply -pthread only when linking.
            if "-pthread" not in linkopts:
                linkopts.append("-pthread")
        elif cflag in [
            "-frounding-math",
            "-ffloat-store",
            "-msse",
            "-msse2",
            "-msse3",
            "-msse4",
            "-msse4.1",
            "-msse4.2",
            "-mfpmath",
        ]:
            # We know these are okay to ignore.
            pass
        else:
            unknown_cflags += [cflag]
    if unknown_cflags:
        print("pkg-config of {} returned flags that we will ignore: {}".format(
            repository_ctx.attr.modname,
            unknown_cflags,
        ))

    # Symlink the absolute include paths into our repository, to obtain
    # relative paths for them as required by cc_library's attributes.
    includes = []
    hdrs_path = repository_ctx.path("include")
    for item in absolute_includes:
        if item == "/usr/include" or item == "/usr/local/include":
            print(("pkg-config of {} returned an include path that " +
                   "contains {} that may contain unrelated headers").format(
                repository_ctx.attr.modname,
                item,
            ))
        symlink_dest = item.replace("/", "_")
        repository_ctx.symlink(
            repository_ctx.path(item),
            hdrs_path.get_child(symlink_dest),
        )
        includes += ["include/" + symlink_dest]
    hdrs_prologue = "glob([\"include/**\"], allow_empty = True) + "

    extra_deprecation = getattr(
        repository_ctx.attr,
        "extra_deprecation",
        "",
    )
    if extra_deprecation == "":
        extra_deprecation = None
    print("[MY_DEBUG]: find inlcudes({}) for {}".format(includes, library_name))

    # Write out the BUILD.bazel file.
    substitutions = {
        "%{topcomment}": "DO NOT EDIT: generated by pkg_config_repository()",
        "%{licenses}": repr(
            getattr(repository_ctx.attr, "licenses", []),
        ),
        "%{library_name}": repr(
            library_name,
        ),
        "%{srcs}": repr(
            getattr(repository_ctx.attr, "extra_srcs", []),
        ),
        "%{hdrs}": (
            hdrs_prologue + repr(
                getattr(repository_ctx.attr, "extra_hdrs", []),
            )
        ),
        "%{copts}": repr(
            getattr(repository_ctx.attr, "extra_copts", []),
        ),
        "%{defines}": repr(
            defines + getattr(repository_ctx.attr, "extra_defines", []),
        ),
        "%{includes}": repr(
            includes + getattr(repository_ctx.attr, "extra_includes", []),
        ),
        "%{linkopts}": repr(
            linkopts + getattr(repository_ctx.attr, "extra_linkopts", []),
        ),
        "%{deps}": repr(
            getattr(repository_ctx.attr, "extra_deps", []),
        ),
        "%{build_epilog}": getattr(repository_ctx.attr, "build_epilog", ""),
        "%{extra_deprecation}": repr(extra_deprecation),
    }
    template = getattr(
        repository_ctx.attr,
        "build_file_template",
        _DEFAULT_TEMPLATE,
    )
    repository_ctx.template("BUILD.bazel", template, substitutions)

    extra_templates = getattr(
        repository_ctx.attr,
        "extra_build_file_templates",
        {},
    )
    for path, template in extra_templates.items():
        repository_ctx.template(path, template, substitutions)

    return struct(error = None)

def setup_pkg_config_repository(repository_ctx):
    """Sets up a pkg-config repository by attempting to use pkg-config or generating an error BUILD file.

    This function attempts to set up the repository using pkg-config. If that fails,
    it generates a BUILD file that will fail at build-time with an error message.

    Args:
      repository_ctx: The repository context object providing access to repository
        attributes and methods for file manipulation.

    Returns:
      A struct with an error field containing an error message string, or None if successful.
    """
    # Check if pkg-config works.
    error = _maybe_setup_pkg_config_repository(repository_ctx).error
    if error == None:
        print("[MY_DEBUG]: use pkg-config for {}".format(repository_ctx.name))
        return struct(error = None)

    # If not, still emit a valid BUILD file but with a library that will fail
    # at build-time (not analysis-time) with the error message.
    library_name = repository_ctx.name.split("+")[-1]
    repository_ctx.file("error.log", """
******************************************************************************
Error in Drake pkg_config repository rule for @{library_name}:
{error}
******************************************************************************
""".format(library_name = library_name, error = error).strip())
    repository_ctx.file("BUILD.bazel", """
load("@rules_cc//cc:cc_library.bzl", "cc_library")
genrule(
    name = "_",
    srcs = ["error.log"],
    outs = ["error.h"],
    cmd = "cat $< 2>&1 && false",
)
cc_library(
    name = {library_name},
    srcs = [":error.h"],
    visibility = ["//visibility:public"],
)""".format(library_name = repr(library_name), error = repr(error)))

    defer_error_os_names = getattr(
        repository_ctx.attr,
        "defer_error_os_names",
        [],
    )
    if repository_ctx.os.name in defer_error_os_names:
        error = None
    return struct(error = error)

def _impl(repository_ctx):
    print("[MY_DEBUG]: use pkg_config_repo_rule for {}".format(repository_ctx.attr.modname))
    result = setup_pkg_config_repository(repository_ctx)
    if result.error != None:
        fail("Unable to complete pkg-config setup for " +
             "@{} repository: {}".format(
                 repository_ctx.name,
                 result.error,
             ))

pkg_config_repository_rule = repository_rule(
    # TODO(jamiesnape): Make licenses mandatory.
    # TODO(jamiesnape): Use of this rule may cause additional transitive
    # dependencies to be linked and their licenses must also be enumerated.
    attrs = {
        "modname": attr.string(mandatory = True),
        "atleast_version": attr.string(),
        "static": attr.bool(default = _DEFAULT_STATIC),
        "build_file_template": attr.label(
            default = _DEFAULT_TEMPLATE,
            allow_files = True,
        ),
        "extra_build_file_templates": attr.string_keyed_label_dict(),
        "extra_srcs": attr.string_list(),
        "extra_hdrs": attr.string_list(),
        "extra_copts": attr.string_list(),
        "extra_defines": attr.string_list(),
        "extra_includes": attr.string_list(),
        "extra_linkopts": attr.string_list(),
        "extra_deps": attr.string_list(),
        "build_epilog": attr.string(),
        "pkg_config_paths": attr.string_list(),
        "extra_deprecation": attr.string(),
        "defer_error_os_names": attr.string_list(),
    },
    local = True,
    configure = True,
    implementation = _impl,
)