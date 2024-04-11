import openai
import sys
import time
import traceback
from os import getenv, path, mkdir
from mbpp import problems
from tqdm import tqdm
from multiprocessing.pool import ThreadPool

openai.api_key = getenv("OPENAI_API_KEY_P")


def collect_generated_healed_code(source_code_path: str, collected_code_path: str) -> None:
    create_output_folders(collected_code_path)
    progress = tqdm(total=len(problems))
    with ThreadPool(processes=20) as threadpool:
        for problem in problems:
            threadpool.apply_async(
                call_llm,
                args=(problem, progress, source_code_path, collected_code_path),
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
        with open(filename, "w+") as f:
            code = str(completion.choices[0].message.content)
            f.write(code)


def call_llm(
    problem: dict[str, str | list[str]],
    progress: tqdm,
    source_code_path: str,
    collected_code_path: str,
    temperature: int = 1,
    top_p: int = 1,
    round: int = 1,
):
    try:
        filename = f"{collected_code_path}/problem-{problem['id']}.txt"
        sourcename = f"{source_code_path}/problem-{problem['id']}.c"
        if path.exists(filename):
            progress.update()
            return (None, None)
        if not path.exists(sourcename):
            progress.update()
            return (None, None)
        print(f"{filename} started.")
        with open(sourcename, "r") as weak_source:
            completion = openai.ChatCompletion.create(
                model="gpt-4",
                messages=[
                    {
                        "role": "user",
                        "content": (
                            "Acting as an experienced C developer, "
                            "analyze the following source-code: "
                            f"{weak_source.read()}\n "
                            "Re-write the source-code, paying attention to "
                            "the comments to check for fixes for the possible "
                            "weaknesses identified. "
                            "Don't forget to add main function, "
                            "and proper includes and function definitions. "
                            "don't write any comments, just write the code."
                        ),
                    },
                ],
                temperature=temperature,
                top_p=top_p,
                max_tokens=4096,
            )
        progress.update()
        print(f"{filename} finished.")
        return (completion, filename)
    except KeyboardInterrupt:
        exit(1)
    except BaseException as ex:
        traceback.print_exc(ex)
        print(
            f"Problem {problem['id']}, temperature {temperature}, Top P {top_p}, round {round}: Connection failed. Retrying..."
        )
        time.sleep(5)
        return call_llm(problem, temperature, top_p, round)


if __name__ == "__main__":
    collect_generated_healed_code(sys.argv[1], sys.argv[2])
