#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char* camel_to_snake(const char* input) {
    if (!input) return NULL;

    regex_t regex;
    int reti = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t max_len = strlen(input) * 2 + 1;
    char* result = (char*)malloc(max_len);
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[3];
    const char* cursor = input;
    char* out_cursor = result;

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[1].rm_eo;
        memcpy(out_cursor, cursor, prefix_len);
        out_cursor += prefix_len;

        *out_cursor++ = '_';

        cursor += pmatch[2].rm_so;
    }

    strcpy(out_cursor, cursor);
    regfree(&regex);

    for (char* p = result; *p; ++p) {
        *p = tolower((unsigned char)*p);
    }

    return result;
}

int main(void) {
    const char* test_cases[] = {
        "camelCase",
        "thisIsATest",
        "already_snake",
        "OneMoreTest",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char* snake = camel_to_snake(test_cases[i]);
        if (snake) {
            printf("%s -> %s\n", test_cases[i], snake);
            free(snake);
        } else {
            fprintf(stderr, "Failed to convert: %s\n", test_cases[i]);
        }
    }

    return 0;
}