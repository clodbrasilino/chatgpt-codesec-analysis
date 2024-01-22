import re
import sys


def get_files_from_folder(search_path) -> list:
    from os import listdir
    from os.path import isfile, join

    return [f for f in listdir(search_path) if isfile(join(search_path, f)) and f[-4:] == ".txt"]


def sanitize_llm_output(input: str) -> str:
    output = input
    output = re.sub(".*```[cC]?\\n", "", output)
    output = re.sub("\\n```[\\s\\S]*", "", output)
    return output


path = f"./collected_code/heal_round_{sys.argv[1]}/healed/"
for filename in get_files_from_folder(path):
    file_content = ""
    with open(path + filename, "r") as txt_file:
        file_content = txt_file.read()
    with open(path + filename[:-4] + ".c", "w") as source_file:
        source_file.write(sanitize_llm_output(file_content))
