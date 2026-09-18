import os

path = "./collected_code_3/round3/heal_0"

for i in range(1, 975):
    os.system(f"mv {path}/problem-{i}-3.txt {path}/problem-{i}.txt")
    os.system(f"mv {path}/problem-{i}-3.c {path}/problem-{i}.c")
    os.system(f"mv {path}/problem-{i}-3.gcc.txt {path}/problem-{i}.gcc.txt")
    os.system(f"mv {path}/problem-{i}-3.o {path}/problem-{i}.o")
