"""
定义工程内通用的变量
"""
def debug_print_var(var_name, var_value):
    print("[MY_DEBUG]: %s: %s" % (var_name, var_value))

def path(repository_ctx, additional_search_paths = []):
    """One-line summary of what this function does.

    Longer description if needed.

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
    search_paths = search_paths + ["/usr/bin", "/bin"]
    final_paths = ":".join(search_paths)
    print("[MY_DEBUG]: path for which(): %s" % final_paths)
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
    exec_result = repository_ctx.execute(["which", program], environment = {
        "PATH": path(repository_ctx, additional_search_paths),
    })
    if exec_result.return_code != 0:
        return None # not found
    return repository_ctx.path(exec_result.stdout.strip())