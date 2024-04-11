import re
import sys
from tqdm import tqdm
from os import listdir
from os.path import isfile, join


def sanitize_llm_outputs_into_sources(path: str):
    filenames = get_files_from_folder(path)
    progress = tqdm(filenames)
    for filename in filenames:
        file_content = ""
        with open(path + "/" + filename, "r") as txt_file:
            file_content = txt_file.read()
        with open(path + "/" + filename[:-4] + ".c", "w") as source_file:
            source_file.write(sanitize_llm_output(file_content))
        progress.update()


def get_files_from_folder(search_path) -> list:
    return [f for f in listdir(search_path) if isfile(join(search_path, f)) and f[-4:] == ".txt"]


def sanitize_llm_output(input: str) -> str:
    output = input
    output = re.sub("[\\s\\S]*```[cC]\\n", "", output)
    output = re.sub("\\n```[\\s\\S]*", "", output)
    return output


if __name__ == "__main__":
    sanitize_llm_outputs_into_sources(sys.argv[1])
