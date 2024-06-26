import os
import sys
from os.path import isfile


def generate_commented_weak_code(input_dir: str, output_dir: str) -> None:
    # Obtain the weaknesses listings from the files
    problems_weaknesses = get_problems_weaknesses(input_dir)

    # Prepare a simpler map for adding the comments to the sources
    pw_map = convert_to_map(problems_weaknesses)

    # Create output directory structure
    create_output_folders(output_dir)

    # Add the comments to the sources (saving on new files)
    for problem_id in range(1, 975):
        # Only write files which has weaknesses found
        if problem_id in pw_map.keys() and pw_map[problem_id] and isfile(f"{input_dir}/problem-{problem_id}.c"):
            with open(f"{input_dir}/problem-{problem_id}.c", "r") as inputfile:
                with open(f"{output_dir}/problem-{problem_id}.c", "w+") as outputfile:
                    try:
                        outputfile.write(add_comments_to_weak_source(input=inputfile.read(), errors=pw_map[problem_id]))
                    except Exception:
                        print(f"problem: {problem_id}")
                        continue


def create_output_folders(path: str) -> None:
    path_elements = path.split("/")
    path = ""
    for i in range(1, len(path_elements)):
        path += path_elements[i] + "/"
        try:
            if i != 1:
                os.mkdir(path)
        except FileExistsError:
            pass


def get_problems_weaknesses(input_dir: str) -> list[dict[str, int | list[dict[str, int | str]]]]:
    problems_weaknesses = []
    for i in range(1, 975):
        errors: dict[str, int | list[dict[str, int | str]]] = {
            "id": i,
            "errors": [],
        }
        text = ""
        if isfile(f"{input_dir}/problem-{i}.c"):
            try:
                with open(f"{input_dir}/problem-{i}.cppcheck.txt", "r") as file:
                    text += file.read()
                    errors["errors"].extend(extract_cppcheck_messages(text))
            except FileNotFoundError:
                pass
            try:
                with open(f"{input_dir}/problem-{i}.flawfinder.txt", "r") as file:
                    text += file.read()
                    errors["errors"].extend(extract_flawfinder_messages(text))
            except FileNotFoundError:
                pass
            try:
                with open(f"{input_dir}/problem-{i}.gcc.txt", "r") as file:
                    text += file.read()
                    errors["errors"].extend(extract_gcc_messages(text))
            except FileNotFoundError:
                pass
            problems_weaknesses.append(errors)
    return problems_weaknesses


def extract_gcc_messages(input: str) -> list[dict[str, int | str]]:
    output = []
    for line in input.split("\n"):
        tokens = line.split(":")
        if len(tokens) == 5:
            output.append({"line": int(tokens[1]), "message": tokens[4]})
    return output


def extract_flawfinder_messages(input: str) -> list[dict[str, int | str]]:
    output = []
    lines = input.split("\n")
    for i in range(0, len(lines)):
        current_line = lines[i]
        tokens = current_line.split(":")
        if len(tokens) == 4:
            reason = ""
            j = i + 1
            next_line = lines[j]
            next_line_tokens = next_line.split(":")
            while len(next_line_tokens) != 4 and next_line != "":
                reason += next_line
                j = j + 1
                next_line = lines[j]
                next_line_tokens = next_line.split(":")
            output.append({"line": int(current_line.split(":")[1]), "message": reason})
    return output


def extract_cppcheck_messages(input: str) -> list[dict[str, int | str]]:
    output = []
    for line in input.split("\n"):
        tokens = line.split(":")
        if len(tokens) == 5:
            output.append({"line": int(tokens[1]), "message": tokens[4]})
    return output


def append_error_messages_into_code(issues: list[str], code: str) -> str:
    error_comments = {}
    for issue in issues:
        line_number = int(str(issue).split(":")[1])
        if line_number not in error_comments.keys():
            error_comments[line_number] = [issue]
        else:
            list(error_comments[line_number]).append(issue)
    code_lines = code.split("\n")
    lines_numbers = list(error_comments.keys()).sort()
    for line in lines_numbers:
        print(line)
        print(code_lines[line - 1])


def add_comments_to_weak_source(input: str, errors: dict[int, list[str]]) -> str:
    error_line_numbers = [x for x in errors.keys()]
    error_line_numbers.sort(reverse=True)
    first_line = "/* Possible weaknesses found:\n"
    weakness_line_start = " * "
    weakness_line_end = "\n"
    last_line_end = " */\n"
    input_lines = input.splitlines(keepends=True)
    for current_line in range(0, len(error_line_numbers)):
        error_line = error_line_numbers[current_line]
        weaknesses_comment = ""
        try:
            padding = leading_spaces(input_lines[error_line - 1])
        except Exception:
            continue
        weaknesses_comment += padding + first_line
        for error_msg in set(errors[error_line]):
            weaknesses_comment += padding + weakness_line_start + error_msg + weakness_line_end
        weaknesses_comment += padding + last_line_end
        input_lines.insert(error_line - 1, weaknesses_comment)
    output = ""
    for line in input_lines:
        output += line
    return output


def leading_spaces(s) -> str:
    import re

    match = re.search(r"^\s*", s)
    leading_spaces_str = ""
    if match.end():
        for i in range(0, match.end()):
            leading_spaces_str += " "
        return leading_spaces_str
    return leading_spaces_str


def convert_to_map(
    problems_weaknesses: list[dict[str, int | list[dict[str, int | str]]]]
) -> dict[int, dict[int, list[str]]]:
    pw_map: dict[int, dict[int, list[str]]] = {}
    for problem in problems_weaknesses:
        pw_map[problem["id"]] = {}
        for error in problem["errors"]:
            if error["line"] not in pw_map[problem["id"]].keys():
                pw_map[problem["id"]][error["line"]] = [error["message"]]
            else:
                pw_map[problem["id"]][error["line"]].append(error["message"])
    return pw_map


if __name__ == "__main__":
    generate_commented_weak_code(sys.argv[1], sys.argv[2])
