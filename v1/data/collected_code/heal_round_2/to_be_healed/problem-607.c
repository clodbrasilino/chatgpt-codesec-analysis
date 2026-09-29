#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int search_pattern(const char* pattern, const char* string) {
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        printf("Error compiling regex pattern\n");
        return -1;
    }

    regmatch_t match;
    result = regexec(&regex, string, 1, &match, 0);
    if (result == REG_NOMATCH) {
        printf("Pattern not found in the string\n");
    } else if (result == 0) {
        printf("Pattern found at position %d\n", match.rm_so);
    } else {
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char error_message[256];
        regerror(result, &regex, error_message, sizeof(error_message));
        printf("Error executing regex: %s\n", error_message);
    }

    regfree(&regex);
    return result;
}

int main() {
    const char string[] = "Hello, this is a test string";
    const char pattern[] = "test";
    search_pattern(pattern, string);

    return 0;
}