"""
定义工程内通用的变量
"""
def debug_print_var(var_name, var_value):
    print("[MY_DEBUG]: %s: %s" % (var_name, var_value))

def path(repository_ctx, additional_search_paths = []):
    """Return the value of the PATH environment variable that would be used by
    the which() command.
    """
    search_paths = additional_search_paths

    # N.B. Ensure ${PATH} in each platform `tools/*.bazelrc` matches these
    # paths.
    search_paths = search_paths + ["/usr/bin", "/bin"]
    final_paths = ":".join(search_paths)
    print("[MY_DEBUG]: path for which(): %s" % final_paths)
    return final_paths

def which(repository_ctx, program, additional_search_paths = []):
    """Return the path of the given program or None if there is no such program
    in the PATH as defined by the path() function above. The value of the
    user's PATH environment variable is ignored.
    """
    exec_result = repository_ctx.execute(["which", program], environment = {
        "PATH": path(repository_ctx, additional_search_paths),
    })
    if exec_result.return_code != 0:
        return None # not found
    return repository_ctx.path(exec_result.stdout.strip())