#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int search_pattern(char* pattern, char* string) {
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
    }
    else if (result == 0) {
        printf("Pattern found at position %d\n", match.rm_so);
    }
    else {
        char error_message[100];
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