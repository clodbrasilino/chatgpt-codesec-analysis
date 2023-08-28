import openai

from os import getenv
from mbpp import problems
from tqdm import tqdm

openai.organization = getenv("OPENAI_ORGANIZATION")
openai.api_key = getenv("OPENAI_KEY")


def collect_generated_code():
    for problem in tqdm(problems):
        completion = openai.ChatCompletion.create(
            model="gpt-4",
            messages=[
                {
                    "role": "user",
                    "content": (
                        "Acting as an experienced C developer, do as follows: "
                        "Considering the following question, output only source-code, nothing else. "
                        "Don't add any type of HTML formatting to the code, as the output should be in plain text. "
                        f"Here's the following question: {problem['text']}"
                    ),
                },
            ],
        )
        with open(f"mbpp-answers/problem-{problem['id']}.c", "w") as f:
            code = str(completion.choices[0].message.content)
            code = code.replace("```c\n", "")
            code = code.replace("```cpp\n", "")
            code = code.replace("```c++\n", "")
            code = code.replace("```C\n", "")
            code = code.replace("```CPP\n", "")
            code = code.replace("```C++\n", "")
            code = code.replace("```\n", "")
            code = code.replace("\n```", "")
            f.write(code)


if __name__ == "__main__":
    collect_generated_code()
