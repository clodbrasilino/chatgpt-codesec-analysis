#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

void snakeToCamel(char* snakeCase, char* camelCase) {
    regex_t regex;
    regmatch_t match;
    int currentIndex = 0;

    regcomp(&regex, "_[a-z]", REG_EXTENDED);

    while (regexec(&regex, &snakeCase[currentIndex], 1, &match, 0) == 0) {
        /* Possible weaknesses found:
         *  Cannot determine that 'snakeCase[match.rm_so+1+currentIndex]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        camelCase[match.rm_so + currentIndex + 1] = toupper(snakeCase[match.rm_so + 1 + currentIndex]);
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        memmove(&snakeCase[match.rm_so + currentIndex], &snakeCase[match.rm_eo + currentIndex + 1], strlen(&snakeCase[match.rm_so + currentIndex]));
        currentIndex += match.rm_eo;
    }

    regfree(&regex);
}

int main() {
    char snakeCase[] = "convert_snake_case";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char camelCase[sizeof(snakeCase)];

    /* Possible weaknesses found:
     *  Cannot determine that 'camelCase[0]' is initialized [premium-bughuntingUninit]
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(camelCase, snakeCase);
    snakeToCamel(camelCase, camelCase);

    printf("Camel case: %s\n", camelCase);

    return 0;
}