#include <stdio.h>
#include <string.h>
#include <regex.h>

#define WORDLEN 5

void find_words(char *string) {
    char *regexString = "\\b\\w{3,5}\\b";
    size_t maxGroups = 1;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
        printf("Could not compile regular expression.\n");
        return;
    };

    char *cursor = string;

    while (!regexec(&regexCompiled, cursor, maxGroups, groupArray, 0)) {
        char cursorCopy[strlen(cursor) + 1];
        strcpy(cursorCopy, cursor);
        cursorCopy[groupArray[0].rm_eo] = 0;
        printf("%s\n", cursorCopy + groupArray[0].rm_so);
        cursor += groupArray[0].rm_eo;
    }

    regfree(&regexCompiled);

    return;
}

int main() {
    char string[] = "This is a test string with some amount of words.";
    find_words(string);
    return 0;
}