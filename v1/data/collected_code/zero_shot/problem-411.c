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
        camelCase[match.rm_so + currentIndex + 1] = toupper(snakeCase[match.rm_so + 1 + currentIndex]);
        memmove(&snakeCase[match.rm_so + currentIndex], &snakeCase[match.rm_eo + currentIndex + 1], strlen(&snakeCase[match.rm_so + currentIndex]));
        currentIndex += match.rm_eo;
    }

    regfree(&regex);
}

int main() {
    char snakeCase[] = "convert_snake_case";
    char camelCase[sizeof(snakeCase)];

    strcpy(camelCase, snakeCase);
    snakeToCamel(camelCase, camelCase);

    printf("Camel case: %s\n", camelCase);

    return 0;
}