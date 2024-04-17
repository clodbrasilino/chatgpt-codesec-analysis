import openai
import sys
import time

from os import getenv, path, mkdir
from mbpp import problems
from tqdm import tqdm
from multiprocessing.pool import ThreadPool

openai.api_key = getenv("OPENAI_API_KEY_P")


def collect_generated_code(collected_code_path: str) -> None:
    create_output_folders(collected_code_path)
    progress = tqdm(total=len(problems))
    with ThreadPool(processes=20) as threadpool:
        for problem in problems:
            # for temperature in range(5):
            # for top_p in range(3):
            threadpool.apply_async(
                call_llm,
                args=(problem, progress, collected_code_path),
                callback=llm_result_callback,
            )
        threadpool.close()
        threadpool.join()


def create_output_folders(path: str) -> None:
    path_elements = path.split("/")
    path = ""
    for i in range(1, len(path_elements)):
        path += path_elements[i] + "/"
        try:
            if i != 1:
                mkdir(path)
        except FileExistsError:
            pass


def llm_result_callback(result):
    completion = result[0]
    filename = result[1]
    if completion and filename:
        with open(filename, "w") as f:
            code = str(completion.choices[0].message.content)
            f.write(code)


def call_llm(problem, progress: tqdm, collected_code_path: str, temperature: int = 1, top_p: int = 1):
    try:
        filename = f"{collected_code_path}/problem-{problem['id']}.txt"
        if path.exists(filename):
            progress.update()
            return (None, None)
        print(f"{filename[:-2]} started.")
        completion = openai.ChatCompletion.create(
            model="gpt-4",
            messages=[
                {
                    "role": "user",
                    "content": (
                        "Acting as an experienced C developer, "
                        f"{problem['text']}. "
                        "Don't forget to add main function, "
                        "and proper includes and function definitions. "
                        "Don't write any comments, just write the code."
                    ),
                },
            ],
            temperature=temperature / 2,
            top_p=top_p / 2,
        )
        progress.update()
        print(f"{filename[:-2]} finished.")
        return (completion, filename)
    except KeyboardInterrupt:
        exit(1)
    except BaseException as ex:
        print(ex)
        print(
            f"Problem {problem['id']}, temperature {temperature}, Top P {top_p}, round {round}: Connection failed. Retrying..."
        )
        time.sleep(5)
        return call_llm(problem, temperature, top_p, round)


if __name__ == "__main__":
    collect_generated_code(sys.argv[1])
