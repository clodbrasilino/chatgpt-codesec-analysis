#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extractBetweenQuotes(const char *str)
{
    regex_t regexCompiled;
    regmatch_t groupArray[2];
    const char *regexPattern = "\"(.*?)\"";

    if (regcomp(&regexCompiled, regexPattern, REG_EXTENDED))
    {
        printf("Could not compile regular expression.\n");
        return;
    };

    char sourceCopy[strlen(str) + 1];
    strcpy(sourceCopy, str);

    if (regexec(&regexCompiled, sourceCopy, 2, groupArray, 0) == 0)
    {
        sourceCopy[groupArray[1].rm_eo] = 0;
        printf("%s\n", sourceCopy + groupArray[1].rm_so);
    }

    regfree(&regexCompiled);
}

int main()
{
    const char testString[] = "the \"quick brown\" fox";
    extractBetweenQuotes(testString);
    return 0;
}