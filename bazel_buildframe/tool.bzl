"""
定义工程内通用的变量
"""

# 参考： https://github.com/RobotLocomotion/drake/blob/master/tools/workspace/execute.bzl
def homebrew_prefix( repository_ctx):
    """Returns the prefix where Homebrew is expected to be found.

    Fails when called on a non-macOS platform.

    Args:
       repository_ctx: The repository context object used to access build
        environment information.

    Returns:
      A string representing the Homebrew prefix path.
    """
    if  repository_ctx.os.name != "mac os x":
        fail("Not a homebrew OS: " +  repository_ctx.os.name)
    if  repository_ctx.os.arch == "x86_64":
        return "/usr/local"
    else:
        return "/opt/homebrew"

def path(repository_ctx, additional_search_paths = []):
    """One-line summary of what this function does.

    Args:
       repository_ctx: The repository context object used to access build
        environment information and execute commands.
      additional_search_paths: List of additional paths to search for
        dependencies or resources.

    Returns:
      A string or path object representing the result of the function.
    """
    search_paths = additional_search_paths

    # N.B. Ensure ${PATH} in each platform `tools/*.bazelrc` matches these
    # paths.
    if  repository_ctx.os.name == "mac os x":
        search_paths = search_paths + [homebrew_prefix( repository_ctx) + "/bin"]
    search_paths = search_paths + ["/usr/bin", "/bin"]
    if  repository_ctx.os.name == "mac os x":
        search_paths = search_paths + ["/usr/sbin", "/sbin"]
    final_paths = ":".join(search_paths)
    return final_paths

def which(repository_ctx, program, additional_search_paths = []):
    """Finds the path of a given program in the search path.

    Return the path of the given program or None if there is no such program
    in the PATH as defined by the path() function above. The value of the
    user's PATH environment variable is ignored.

    Args:
      repository_ctx: The repository context object.
      program: The name of the program to find.
      additional_search_paths: Additional paths to search before default paths.

    Returns:
      The path to the program, or None if not found.
    """
    final_path = path(repository_ctx, additional_search_paths)
    print("[MY_DEBUG]: search path: %s" % final_path)
    exec_result = repository_ctx.execute(["which", program], environment = {
        "PATH": final_path,
    })
    if exec_result.return_code != 0:
        return None # not found
    return repository_ctx.path(exec_result.stdout.strip())