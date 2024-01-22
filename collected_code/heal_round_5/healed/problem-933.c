#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

void camelToSnake(char *str) {
    char pattern[] = "([A-Z])";
    char replacement[] = "_\\1";
    regex_t regex;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation failed");
        return;
    }

    if (str == NULL) {
        return;
    }

    size_t length = strlen(str);
    if (str[length] != '\0') {
        printf("Non-\\0-terminated strings are not allowed\n");
        return;
    }
    
    length += regerror(0, &regex, NULL, 0) + 1;

    char *result = (char *)malloc(length);
    
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    regmatch_t match;
    int offset = 0;
    size_t i = 0;
    
    while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        int start = match.rm_so;
        int end = match.rm_eo;
        int matchedLength = end - start;

        strncpy(result + i, str + offset, start);
        i += start;

        strncpy(result + i, replacement, strlen(replacement));
        i += strlen(replacement);

        offset += end;
    }
    
    strncpy(result + i, str + offset, strlen(str + offset));
    result[length-1] = '\0';

    printf("%s\n", result);
    
    free(result);
    regfree(&regex);
}

int main() {
    char input[] = "camelCaseString";
    camelToSnake(input);
    
    return 0;
}