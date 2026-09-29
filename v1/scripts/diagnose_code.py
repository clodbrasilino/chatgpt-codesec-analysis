import os
import sys
import time
import tqdm
from multiprocessing.pool import ThreadPool

threadpool_size = 6


def diagnose_code(path: str):
    try:
        source_files = []
        for file in os.listdir(path):
            if file.endswith(".c"):
                source_files.append(file)
        with ThreadPool(processes=threadpool_size) as threadpool:
            for file in tqdm.tqdm(source_files, "Diagnosing code: "):
                if file.endswith(".c"):
                    if not os.path.exists(path + file[:-2] + ".clang.txt"):
                        command = f"bash ./diagnose_code.sh {path}{file}"
                        time.sleep(0.001)
                        threadpool.apply(os.system, args=(command,), kwds={})
            threadpool.close()
            threadpool.join()
    except KeyboardInterrupt:
        exit(1)


if __name__ == "__main__":
    path = sys.argv[1] if sys.argv[1] else ""
    diagnose_code(path)
