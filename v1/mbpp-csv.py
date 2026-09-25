import csv
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))  # bct.py stays in the repo root
from bct import problems

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
