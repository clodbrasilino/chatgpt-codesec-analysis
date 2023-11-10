import csv
from mbpp import problems

mbpp_csv: list[dict] = []
for problem in problems:
    mbpp_csv.append(
        {
            "id": problem["id"],
            "problemtype": problem["label"],
        }
    )
with open("problem-types.csv", "w", newline="") as of:
    dict_writer = csv.DictWriter(of, mbpp_csv[0].keys())
    dict_writer.writeheader()
    dict_writer.writerows(mbpp_csv)
