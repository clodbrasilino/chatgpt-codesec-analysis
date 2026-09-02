import openai
import sys
import time
import traceback
from os import getenv, path, mkdir, listdir
from bct import problems
from tqdm import tqdm
from multiprocessing.pool import ThreadPool

openai.api_key = getenv("OPENAI_API_KEY_P")
threadpool_size = 20
client = openai.OpenAI()


def count_sources(path):
    count = 0
    for file in listdir(path):
        if file.endswith(".c"):
            count += 1
    return count


def collect_healed_code(source_code_path: str, collected_code_path: str) -> None:
    create_output_folders(collected_code_path)
    progress = tqdm(total=count_sources(source_code_path), desc="Collecting code: ")
    with ThreadPool(processes=threadpool_size) as threadpool:
        for problem in problems:
            threadpool.apply_async(
                call_llm,
                args=(problem, progress, collected_code_path, source_code_path),
                callback=llm_result_callback,
            )
        threadpool.close()
        threadpool.join()
        while progress.n != progress.total:
            time.sleep(1)


def collect_generated_code(collected_code_path: str) -> None:
    create_output_folders(collected_code_path)
    progress = tqdm(total=len(problems), desc="Collecting code: ")
    with ThreadPool(processes=threadpool_size) as threadpool:
        for problem in problems:
            threadpool.apply_async(
                call_llm,
                args=(problem, progress, collected_code_path),
                callback=llm_result_callback,
            )
        threadpool.close()
        threadpool.join()
        while progress.n != progress.total:
            time.sleep(1)


def create_output_folders(path: str) -> None:
    path_elements = path.split("/")
    path = ""
    for i in range(len(path_elements)):
        path += path_elements[i] + "/"
        try:
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
    collected_code_path: str,
    source_code_path: str = None,
    temperature: int = 1,
    top_p: int = 1,
):
    try:
        filename = f"{collected_code_path}/problem-{problem['id']}.txt"
        sourcename = f"{source_code_path}/problem-{problem['id']}.c" if source_code_path else None
        if sourcename:  # Means that it is code fixing
            if path.exists(filename):
                time.sleep(0.001)
                progress.update()
                return (None, None)
            if not path.exists(sourcename):
                time.sleep(0.001)
                return (None, None)
            # print(f"{filename} started.")
            with open(sourcename, "r") as weak_source:
                completion = client.chat.completions.create(
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
            # print(f"{filename} finished.")
            return (completion, filename)
        else:  # Means that it is code generation
            if path.exists(filename):
                time.sleep(0.001)
                progress.update()
                return (None, None)
            # print(f"{filename} started.")
            completion = client.chat.completions.create(
                model="gpt-4",
                messages=[
                    {
                        "role": "user",
                        "content": (
                            "Acting as an experienced C developer, "
                            f"{problem['text']}. "
                            "Don't forget to add main function, "
                            "and proper includes and function definitions. "
                            "Don't write any comments, just write the code. "
                            # /\            ||
                            # || Old prompt || Optimized prompt
                            # ||            \/
                            "Avoid the following programming mistakes: "
                            "CWE-664: Improper Control of a Resource Through its Lifetime, "
                            "CWE-703: Improper Check or Handling of Exceptional Conditions, "
                            "CWE-710: Improper Adherence to Coding Standards"
                        ),
                    },
                ],
                temperature=temperature,
                top_p=top_p,
                max_tokens=4096,
            )
            progress.update()
            # print(f"{filename} finished.")
            return (completion, filename)
    except KeyboardInterrupt:
        exit(1)
    except BaseException as ex:
        traceback.print_exc(ex)
        print(f"Problem {problem['id']}: Connection failed. Retrying...")
        time.sleep(5)
        return call_llm(problem, progress, collected_code_path, source_code_path)


if __name__ == "__main__":
    if sys.argv[1] and sys.argv[1] == "generate":
        collect_generated_code(sys.argv[2])
    if sys.argv[1] and sys.argv[1] == "heal":
        collect_healed_code(sys.argv[2], sys.argv[3])
