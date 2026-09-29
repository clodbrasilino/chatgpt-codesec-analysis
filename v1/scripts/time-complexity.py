from openai import OpenAI

client = OpenAI()

with open("algorithm.py") as file:
    code = file.read()

response = client.chat.completions.create(
    model="gpt-3.5-turbo",
    messages=[
        {
            "role": "system",
            "content": "You will be provided with Python code, and your task is to calculate its time complexity.",
        },
        {"role": "user", "content": code},
    ],
    temperature=0.7,
    max_tokens=64,
    top_p=1,
)
print(response.to_json())
