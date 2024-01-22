FOLDER=collected_code

echo Total sources generated: `ls -l $FOLDER/*.c | wc -l`
# 871

echo Compiled sources: `ls -l $FOLDER/*.o | wc -l`
# 855

echo cppcheck issues found: `cat $FOLDER/*.cppcheck.txt | grep '\[.*\]$' | wc -l`
# 29

echo gcc issues found: `cat $FOLDER/*.gcc.txt | grep '\[-W.*\]' | wc -l`
# 99

echo flawfinder issues found: `cat $FOLDER/*.flawfinder.txt | grep '(CWE.*)' | wc -l`
# 332