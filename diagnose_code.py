import os
import sys


def diagnose_code(path: str):
    os.system(f"./diagnose_code.sh{' ' if path else ''}{path}")


if __name__ == "__main__":
    path = sys.argv[1] if sys.argv[1] else ""
    diagnose_code(path)
