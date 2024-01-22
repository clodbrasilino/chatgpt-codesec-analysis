FOLDER=collected_code/heal_round_15/healed

echo Total sources generated: `ls -l $FOLDER/*.c | wc -l`
# 871

echo Compiled sources: `ls -l $FOLDER/*.o | wc -l`
# 855

echo Uncompiled sources: `python3 report_uncompiled_healed_code.py`
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
# 871 - 855 = 16

echo cppcheck issues found: `cat $FOLDER/*.cppcheck.txt | grep '\[.*\]$' | wc -l`
# 29

echo gcc issues found: `cat $FOLDER/*.gcc.txt | grep '\[-W.*\]' | wc -l`
# 99

echo flawfinder issues found: `cat $FOLDER/*.flawfinder.txt | grep '(CWE.*)' | wc -l`
# 332