import re


def get_files_from_folder(search_path) -> list:
    from os import listdir
    from os.path import isfile, join

    return [f for f in listdir(search_path) if isfile(join(search_path, f))]


def extract_code(input):
    return re.findall("```[cC][\\s\\S]*```", input)[0][5:-4]


path = "./collected_code_2/"
for filename in get_files_from_folder(path):
    file_content = ""
    with open(path + filename, "r") as txt_file:
        file_content = txt_file.read()
    with open(path + filename[:-4] + ".c", "x") as source_file:
        source_file.write(extract_code(file_content))
