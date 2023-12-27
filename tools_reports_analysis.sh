# Total sources generated
ls -l collected_code/healed/*.c | wc -l
# 871

# Compiled sources
ls -l collected_code/healed/*.o | wc -l
# 855

# Uncompiled sources: 871 - 855 = 16
python3 report_uncompiled_healed_code.py
# List of uncompiled sources:
# problem-8.c
# problem-74.c
# problem-75.c
# problem-201.c
# problem-401.c
# problem-424.c
# problem-533.c
# problem-586.c
# problem-591.c
# problem-625.c
# problem-665.c
# problem-730.c
# problem-805.c
# problem-853.c
# problem-936.c
# problem-947.c

# cppcheck issues found
cat collected_code/healed/*.cppcheck.txt | grep '\[.*\$]' | wc -l
# 29

# gcc issues found
cat collected_code/healed/*.gcc.txt | grep '\[-W.*\]' | wc -l
# 99

# flawfinder issues found
cat collected_code/healed/*.flawfinder.txt | grep '(CWE.*)' | wc -l
# 332