#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define ERROR_MESSAGE_SIZE 1024

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
        char *error_message = (char*) malloc(ERROR_MESSAGE_SIZE * sizeof(char));
        if (error_message != NULL) {
            regerror(result, &regex, error_message, ERROR_MESSAGE_SIZE);
            printf("Error executing regex: %s\n", error_message);
            free(error_message);
        } else {
            printf("Failed to allocate memory for error message\n");
        }
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