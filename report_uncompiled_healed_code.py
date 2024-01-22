from os import listdir
from os.path import isfile, join


def get_files_from_folder(search_path) -> list:
    return [f for f in listdir(search_path) if isfile(join(search_path, f)) and f[-2:] == ".c"]


path = "./collected_code/heal_round_15/healed/"
uncompiled = []
for filename in get_files_from_folder(path):
    if not isfile(join(path, filename[:-2] + ".o")):
        uncompiled.append(filename)
print(len(uncompiled))
# for filename in uncompiled:
#     print(filename)
