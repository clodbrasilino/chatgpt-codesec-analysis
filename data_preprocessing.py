from os import listdir, mkdir
import re
import pandas
import sys
from cwe2.database import Database
from cwe2.weakness import Weakness


interesting_words = [
    # cppcheck
    "[premium-bughuntingUninitNonConstArg]",
    "[premium-bughuntingUninit]",
    "[uninitvar]",
    "[zerodiv]",
    "[arrayIndexOutOfBounds]",
    "[legacyUninitvar]",
    "[negativeIndex]",
    "[integerOverflow]",
    "[syntaxError]",
    "[invalidFunctionArg]",
    "[uninitStructMember]",
    "[uninitdata]",
    "[overlappingWriteFunction]",
    # gcc
    "[-Wimplicit-function-declaration]",
    "[-Wbuiltin-declaration-mismatch]",
    "[-Wanalyzer-possible-null-dereference]",  # [CWE-690]
    "[-Wincompatible-pointer-types]",
    "[-Wsizeof-array-argument]",
    "[-Wanalyzer-null-dereference]",  # [CWE-476]
    "[-Wanalyzer-malloc-leak]",  # [CWE-401]
    "[-Wanalyzer-write-to-string-literal]",
    "[-Wanalyzer-out-of-bounds]",  # [CWE-126]
    "[-Wanalyzer-use-of-uninitialized-value]",  # [CWE-457]
    "[-Wint-conversion]",
    "[-Wanalyzer-out-of-bounds]",  # [CWE-127]
    "[-Wanalyzer-null-argument]",  # [CWE-476]
    "[-Wreturn-local-addr]",
    "[-Wanalyzer-free-of-non-heap]",  # [CWE-590]
    # flawfinder
    "(CWE-120, CWE-20)",
    "(CWE-126)",
    "(CWE-120)",
    "(CWE-190)",
]

cwe_mapping = {
    20: [  # https://cwe.mitre.org/data/definitions/20.html
        "(CWE-120, CWE-20).",
    ],
    119: [  # https://cwe.mitre.org/data/definitions/119.html
        "[arrayIndexOutOfBounds]",
        "(CWE-119!/CWE-120).",
    ],
    120: [  # https://cwe.mitre.org/data/definitions/120.html
        "(CWE-120, CWE-20)",
        "(CWE-119!/CWE-120)",
        "(CWE-120)",
    ],
    123: [  # https://cwe.mitre.org/data/definitions/123.html
        "[-Wanalyzer-write-to-string-literal]",  # might also be mapped as CWE-134 maybe.
    ],
    124: [  # https://cwe.mitre.org/data/definitions/124.html
        "[CWE-124]",
    ],
    126: [  # https://cwe.mitre.org/data/definitions/126.html
        "(CWE-126)",
        "[-Wanalyzer-out-of-bounds]",
    ],
    127: [  # https://cwe.mitre.org/data/definitions/127.html
        "[-Wanalyzer-out-of-bounds]",
    ],
    129: [  # https://cwe.mitre.org/data/definitions/129.html
        "[negativeIndex]",
    ],
    190: [  # https://cwe.mitre.org/data/definitions/190.html
        "[integerOverflow]",
        "(CWE-190)",
    ],
    369: [  # https://cwe.mitre.org/data/definitions/369.html
        "[zerodiv]",
    ],
    401: [  # https://cwe.mitre.org/data/definitions/401.html
        "[-Wanalyzer-malloc-leak]",
        "[memleak]",
    ],
    457: [  # https://cwe.mitre.org/data/definitions/457.html
        "[uninitvar]",
        "[legacyUninitvar]",
        "[uninitStructMember]",
        "[-Wanalyzer-use-of-uninitialized-value]",
        "[uninitdata]",
        "undeclared (first use in this function)",
    ],
    467: [  # https://cwe.mitre.org/data/definitions/467.html
        "[-Wsizeof-array-argument]",
    ],
    476: [  # https://cwe.mitre.org/data/definitions/476.html
        "[-Wanalyzer-null-dereference]",
        "[-Wanalyzer-null-argument]",
    ],
    562: [  # https://cwe.mitre.org/data/definitions/562.html
        "[-Wreturn-local-addr]",
    ],
    590: [  # https://cwe.mitre.org/data/definitions/590.html
        "[-Wanalyzer-free-of-non-heap]",
    ],
    628: [  # https://cwe.mitre.org/data/definitions/628.html
        "[invalidFunctionArg]",
    ],
    690: [  # https://cwe.mitre.org/data/definitions/690.html
        "[-Wanalyzer-possible-null-dereference]",
    ],
    704: [  # https://cwe.mitre.org/data/definitions/704.html
        "[-Wint-conversion]",
    ],
    758: [  # https://cwe.mitre.org/data/definitions/758.html
        "[-Wimplicit-function-declaration]",
        "[-Wbuiltin-declaration-mismatch]",
        "conflicting types for",
        "unknown type name",
    ],
    787: [  # https://cwe.mitre.org/data/definitions/787.html
        "excess elements in array initializer",
    ],
    843: [  # https://cwe.mitre.org/data/definitions/843.html
        "[-Wincompatible-pointer-types]",
    ],
    1260: [  # https://cwe.mitre.org/data/definitions/1260.html
        "[overlappingWriteFunction]",
    ],
}


def create_output_folder(path: str) -> None:
    path_elements = path.split("/")
    path = ""
    for i in range(len(path_elements)):
        path += path_elements[i] + "/"
        try:
            if i != 1:
                mkdir(path)
        except FileExistsError:
            pass


def extract_flawfinder_ocurrences(input: str, filename: str) -> list[dict[str, str | int]]:
    output = list()
    results_block = input.split("RESULTS:")[1].split("ANALYSIS")[0]
    if results_block.strip() == "":
        return output
    errors = results_block.replace("\n", "").split("collected")
    for error in errors:
        if "(CWE-" in error:
            output.append(
                {
                    "tool": filename.split(".")[1],
                    "token": re.findall(r"(\(CWE-.*?\))", error)[0],
                    "file": filename,
                    "problem_number": int(filename.split("-")[1].split(".")[0]),
                    "line_number": int(error.split(":")[1]),
                }
            )
    return output


def extract_gcc_cppcheck_ocurrences(input: str, filename: str) -> list[dict[str, str | int]]:
    output = list()
    for line in input.split("\n"):
        for word in interesting_words:
            if word in line:
                output.append(
                    {
                        "tool": filename.split(".")[1],
                        "token": word,
                        "file": filename,
                        "problem_number": int(filename.split("-")[1].split(".")[0]),
                        "line_number": int(line.split(":")[1]),
                    }
                )
    return output


def count_ocurrences() -> list[dict]:
    code_files = listdir(dataset_dir)
    ocurrences = list()
    for code_file in code_files:
        if (
            code_file.endswith(".cppcheck.txt")
            or code_file.endswith(".flawfinder.txt")
            or code_file.endswith(".gcc.txt")
        ):
            with open(f"{dataset_dir}{code_file}", "r") as open_file:
                wholefile = open_file.read()
                if code_file.endswith(".flawfinder.txt"):
                    ocurrences.extend(extract_flawfinder_ocurrences(wholefile, code_file))
                else:
                    ocurrences.extend(extract_gcc_cppcheck_ocurrences(wholefile, code_file))
    return ocurrences


def fd_cwes_by_problem(ocurrences: list[dict]) -> list[dict]:
    fd_dict = {}
    for ocurrence in ocurrences:
        for key in cwe_mapping.keys():
            if ocurrence["token"] in cwe_mapping[key]:
                pn = ocurrence["problem_number"]
                tool = ocurrence["tool"]
                if f"{pn}:{key}:{tool}" in fd_dict.keys():
                    fd_dict[f"{pn}:{key}:{tool}"] += 1
                else:
                    fd_dict[f"{pn}:{key}:{tool}"] = 1
    fd = list()
    for key in fd_dict.keys():
        key = str(key)  # for better syntax highlighting
        fd.append(
            {
                "problem": key.split(":")[0],
                "cwe": key.split(":")[1],
                "tool": key.split(":")[2],
                "frequency": fd_dict[key],
            }
        )
    return fd


def fd_pillars_by_problem(ocurrences: list[dict]) -> list[dict]:
    fd_dict = {}
    for ocurrence in ocurrences:
        for key in cwe_mapping.keys():
            if ocurrence["token"] in cwe_mapping[key]:
                pn = ocurrence["problem_number"]
                tool = ocurrence["tool"]
                if f"{pn}:{key}:{tool}" in fd_dict.keys():
                    fd_dict[f"{pn}:{key}:{tool}"] += 1
                else:
                    fd_dict[f"{pn}:{key}:{tool}"] = 1
    fd = list()
    for key in fd_dict.keys():
        key = str(key)  # for better syntax highlighting
        pillar = get_cwe_pillar(int(key.split(":")[1]))
        fd.append(
            {
                "problem": key.split(":")[0],
                "cwe": pillar,
                "tool": key.split(":")[2],
                "frequency": fd_dict[key],
            }
        )
    return fd


def get_cwe_pillar(cwe: int):
    db = Database()
    current_cwe = db.get(cwe)
    current_cwe_father = find_father(current_cwe)
    while current_cwe_father:
        current_cwe = db.get(current_cwe_father)
        current_cwe_father = find_father(current_cwe)
    return current_cwe.cwe_id


def find_father(cwe: Weakness):
    for related in cwe.related_weaknesses.split("::"):
        if related == "":
            continue
        related_parts = related.split(":")
        if related_parts[1] == "ChildOf" and related_parts[5] == "1000":
            return int(related_parts[3])
    return None


if __name__ == "__main__":
    dataset_dir = sys.argv[1]
    create_output_folder(dataset_dir + "/stats/")
    values = []
    [values.extend(x) for x in cwe_mapping.values()]
    for i in interesting_words:
        if i not in values:
            print(i)
    ocurrences = count_ocurrences()
    ocurrences_df = pandas.DataFrame(ocurrences)
    ocurrences_df.to_csv(f"{dataset_dir}stats/word_ocurrences.csv", index=False)
    ocurrences_df.head()
    fd = fd_cwes_by_problem(ocurrences)
    fd_df = pandas.DataFrame(fd)
    fd_df.to_csv(f"{dataset_dir}stats/cwes_by_problem.csv", index=False)
    fd_df.head()
    pillar_fd = fd_pillars_by_problem(ocurrences)
    pillar_fd_df = pandas.DataFrame(pillar_fd)
    pillar_fd_df.to_csv(f"{dataset_dir}stats/cwes_by_pillar.csv", index=False)
    pillar_fd_df.head()
    exploded_fd = list[dict]()
    fields_set = set()
    for item in pillar_fd:
        new_item = {}
        new_item["problem"] = item["problem"]
        for field in item.keys():
            if field not in ("problem", "frequency"):
                fields_set.add(f"{field}_{item[field]}")
                new_item[f"{field}_{item[field]}"] = item["frequency"]
        exploded_fd.append(new_item)
    for item in exploded_fd:
        for field in fields_set:
            if field not in item.keys():
                item[field] = 0
    exploded_fd_df = pandas.DataFrame(exploded_fd)
    exploded_fd_df.to_csv(f"{dataset_dir}stats/exploded_cwes_tools.csv", index=False)
    print(f"data preprocessing for {dataset_dir} finished.")
