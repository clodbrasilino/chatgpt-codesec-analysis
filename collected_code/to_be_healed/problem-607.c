#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int search_pattern(char* pattern, char* string) {
    regex_t regex;
    /* Possible weaknesses found:
     *  Cannot determine that 'pattern[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        printf("Error compiling regex pattern\n");
        return -1;
    }

    regmatch_t match;
    /* Possible weaknesses found:
     *  Cannot determine that 'string[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    result = regexec(&regex, string, 1, &match, 0);
    if (result == REG_NOMATCH) {
        printf("Pattern not found in the string\n");
    }
    else if (result == 0) {
        printf("Pattern found at position %d\n", match.rm_so);
    }
    else {
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char error_message[100];
        /* Possible weaknesses found:
         *  Cannot determine that 'error_message[0]' is initialized [premium-bughuntingUninit]
         */
        regerror(result, &regex, error_message, sizeof(error_message));
        printf("Error executing regex: %s\n", error_message);
    }

    regfree(&regex);
    return result;
}

int main() {
    char string[] = "Hello, this is a test string";
    char pattern[] = "test";
    search_pattern(pattern, string);

    return 0;
}