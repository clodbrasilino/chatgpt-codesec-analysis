#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t input_len = strnlen(input, 1048576);
    size_t max_len = (input_len * 2) + 1;
    char *result = (char *)calloc(max_len, sizeof(char));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    char *res_cursor = result;
    size_t remaining = max_len;
    regmatch_t pmatch[3];

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t prefix_len = (size_t)pmatch[1].rm_eo;
        
        if (prefix_len >= remaining) {
            break;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(res_cursor, cursor, prefix_len);
        res_cursor += prefix_len;
        remaining -= prefix_len;
        
        if (remaining > 1) {
            *res_cursor = '_';
            res_cursor++;
            remaining--;
        }
        
        cursor += pmatch[2].rm_so;
    }

    if (remaining > 0) {
        snprintf(res_cursor, remaining, "%s", cursor);
    }
    
    regfree(&regex);

    for (char *p = result; *p != '\0'; ++p) {
        *p = (char)tolower((unsigned char)*p);
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "camelCase",
        "thisIsATest",
        "already_snake_case",
        "convert123ToSnake",
        "SimpleTest",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; ++i) {
        char *snake = camel_to_snake(test_cases[i]);
        if (snake != NULL) {
            printf("%s -> %s\n", test_cases[i], snake);
            free(snake);
        } else {
            fprintf(stderr, "Failed to convert %s\n", test_cases[i]);
        }
    }

    return 0;
}