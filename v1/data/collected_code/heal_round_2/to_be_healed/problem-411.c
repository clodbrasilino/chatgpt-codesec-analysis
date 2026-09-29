#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_STRING_SIZE 256

void snakeToCamel(char* snakeCase, char* camelCase) {
    regex_t regex;
    regmatch_t match;
    int currentIndex = 0;

    regcomp(&regex, "_[a-z]", REG_EXTENDED);

    while (regexec(&regex, &snakeCase[currentIndex], 1, &match, 0) == 0) {
        if(snakeCase[match.rm_so+1+currentIndex] == '\0') {
            break;
        }
        camelCase[match.rm_so + currentIndex + 1] = toupper(snakeCase[match.rm_so + 1 + currentIndex]);
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        size_t length = strlen(&snakeCase[match.rm_so + currentIndex]);
        memmove(&snakeCase[match.rm_so + currentIndex], &snakeCase[match.rm_eo + currentIndex + 1], length);
        currentIndex += match.rm_eo;
        camelCase[currentIndex] = '\0';
    }

    regfree(&regex);
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char snakeCase[MAX_STRING_SIZE] = "convert_snake_case";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char camelCase[MAX_STRING_SIZE];

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(camelCase, snakeCase, MAX_STRING_SIZE-1);
    camelCase[MAX_STRING_SIZE-1] = '\0';
    snakeToCamel(camelCase, camelCase);
    printf("Camel case: %s\n", camelCase);

    return 0;
}