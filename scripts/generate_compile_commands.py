'''
script to generate compile_commands.json, do not depend on external py lib
'''
import shutil
import logging
import subprocess
import os
import argparse

_G_PARSER = argparse.ArgumentParser(
    description="script to generate compile_commands.json"
)
_G_PARSER.add_argument("-o",
                       "--option",
                       type=str,
                       required=True,
                       help="bazel compile args")
_G_PARSER.add_argument("-t",
                       "--target",
                       type=str,
                       help="bazel build target",
                       default="//...")

logging.basicConfig(
    level=logging.DEBUG,
    format="[%(asctime)s][%(name)s][%(levelname)s]: %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S"
)
_G_BAZEL_COMPILE_COMMANDS_TOOL = "bazel-compile-commands"
_G_JSON_FORMAT_TOOL = "jq"
_G_BAZEL_BUILD_ARGS = ""
_G_BAZEL_COMPILE_COMMANDS_ARGS = ""
_G_BAZEL_EXTERNAL_PATH = "./external"

def _run_shell_cmd(cmd: str, cwd: str):
    logging.debug("run cmd in %s: %s", cwd, cmd)
    try:
        ret_val = subprocess.run(
            cmd,
            shell=True,
            capture_output=True,
            text=True,
            encoding="utf-8",
            check=True,
            cwd=cwd
        )
    except subprocess.CalledProcessError as e:
        logging.error("run cmd failed\ncmd(%s)\nreturncode(%d)",
                      cmd, e.returncode)
        print(f"{e.stderr}")
        return -1, None
    return 0, ret_val

def _get_current_bazel_workspace() -> str:
    cmd = "bazel info workspace"
    cur_dir = os.getcwd()
    ret_code, ret_val = _run_shell_cmd(cmd, cur_dir)
    if ret_code != 0:
        logging.error("get bazel info workspace failed")
        return ""
    logging.info("current workspace: %s", ret_val.stdout.strip())
    return ret_val.stdout.strip()

# def _get_current_bazel_output_base() -> str:
#     cmd = "bazel info output_base"
#     cur_dir = os.getcwd()
#     ret_code, ret_val = _run_shell_cmd(cmd, cur_dir)
#     if ret_code != 0:
#         logging.error("get bazel info output_base failed")
#         return ""
#     logging.info("current output_base: %s", ret_val.stdout.strip())
#     return ret_val.stdout.strip()

def _check_if_tool_exist(tool_name: str) -> bool:
    if shutil.which(tool_name) is not None:
        return True
    return False

def generate_compile_commands() -> int:
    if _check_if_tool_exist(_G_BAZEL_COMPILE_COMMANDS_TOOL) is False:
        logging.error("cannot find %s in system",
                      _G_BAZEL_COMPILE_COMMANDS_TOOL)
        return -1
    logging.info("%s exist", _G_BAZEL_COMPILE_COMMANDS_TOOL)

    bazel_workspace_path = _get_current_bazel_workspace()
    if bazel_workspace_path == "":
        logging.error("get bazel workspace failed")
        return -1

    cmd = _G_BAZEL_COMPILE_COMMANDS_TOOL + " " + _G_BAZEL_COMPILE_COMMANDS_ARGS
    ret_code, _ = _run_shell_cmd(cmd, bazel_workspace_path)
    if ret_code != 0:
        logging.error("generate compile_commands.json failed")
        return -1
    return 0

def format_compile_json(json_path: str) -> int:
    if _check_if_tool_exist(_G_JSON_FORMAT_TOOL) is False:
        logging.error("cannot find %s in system",
                      _G_JSON_FORMAT_TOOL)
        return -1
    cmd = f"jq . {json_path} > tmp.json && mv tmp.json {json_path}"
    ret_code, _ = _run_shell_cmd(cmd, os.getcwd())
    if ret_code != 0:
        logging.error("format %s failed", json_path)
        return -1
    return 0

def replace_bazel_exec_path(json_path) -> int:
    cmd = "bazel info execution_root"
    ret_code, ret_val = _run_shell_cmd(cmd=cmd, cwd=os.getcwd())
    if ret_code != 0:
        logging.error("get bazel execution_root failed")
        return -1
    bazel_exec_root_path = ret_val.stdout.strip()
    current_workspace_path = _get_current_bazel_workspace()

    logging.info("replace %s with %s", bazel_exec_root_path,
                 current_workspace_path)
    try:
        with open(json_path, "r", encoding="utf-8") as json_file:
            json_data = json_file.read()
            new_json_data = json_data.replace(bazel_exec_root_path,
                                              current_workspace_path)

        with open(json_path, "w", encoding="utf-8") as json_file:
            json_file.write(new_json_data)
    except Exception as e:
        logging.error("replace file content failed, %s", str(e))
        return -1

    # create symlink to output_base external
    virtual_external_path = os.path.join(current_workspace_path, _G_BAZEL_EXTERNAL_PATH)
    if os.path.islink(virtual_external_path):
        logging.info("%s exist, do not create again", virtual_external_path)
    else:
        logical_workspace_name = os.path.join(current_workspace_path,
            "bazel-" + os.path.basename(_get_current_bazel_workspace()))
        real_external_path = os.path.join(logical_workspace_name, _G_BAZEL_EXTERNAL_PATH)
        os.symlink(real_external_path, virtual_external_path)
    return 0

if __name__ == "__main__":
    args = _G_PARSER.parse_args()
    _G_BAZEL_BUILD_ARGS = args.option
    logging.info("BAZEL_BUILD_ARGS: %s", _G_BAZEL_BUILD_ARGS)
    build_target = args.target

    _G_BAZEL_COMPILE_COMMANDS_ARGS = (
        "--verbose "
        "--resolve "
        f"--target {build_target} "
        f"-b \"{_G_BAZEL_BUILD_ARGS}\" "
    )
    logging.info("BAZEL_COMPILE_COMMANDS_ARGS: %s", _G_BAZEL_COMPILE_COMMANDS_ARGS)

    if generate_compile_commands() != 0:
        logging.error("generate compile commands failed")
        exit(-1)
    logging.info("generate compile commands done")

    json_full_path = os.path.join(_get_current_bazel_workspace(),
                                  "compile_commands.json")
    if format_compile_json(json_full_path) != 0:
        logging.error("format compile_commands.json failed")
        exit(-1)
    logging.info("format compile_commands.json done")

    if replace_bazel_exec_path(json_full_path) != 0:
        logging.error("replace json content failed")
        exit(-1)
    logging.info("replace compile_commands.json content done")
    exit(0)
