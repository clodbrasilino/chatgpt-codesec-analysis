import csv
import os.path

dataset: list[dict] = []
for i in range(1, 975):
    with open(f"collected_code/problem-{i}.c") as scf:
        sc = scf.read().replace("\n", "\\n")
    compiled = os.path.isfile(f"collected_code/problem-{i}.o")
    with open(f"collected_code/problem-{i}.cppcheck.txt") as cppcf:
        cppcheck = cppcf.read().replace("\n", "\\n")
    with open(f"collected_code/problem-{i}.flawfinder.txt") as fff:
        flawfinder = fff.read().replace("\n", "\\n")
    with open(f"collected_code/problem-{i}.gcc.txt") as gccf:
        gcc = gccf.read().replace("\n", "\\n")
    dataset.append(
        {
            "problem": i,
            "compiled": compiled,
            "cppcheck": cppcheck,
            "flawfinder": flawfinder,
            "gcc": gcc,
        }
    )
keys = dataset[0].keys()
with open("dataset.csv", "w+", newline="") as dataset_file:
    writer = csv.DictWriter(dataset_file, keys, delimiter="§")
    writer.writeheader()
    writer.writerows(dataset)
