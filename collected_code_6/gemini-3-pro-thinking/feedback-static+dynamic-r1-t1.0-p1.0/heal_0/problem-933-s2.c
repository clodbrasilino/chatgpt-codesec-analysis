#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char* convert_camel_to_snake(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t max_len = strlen(input) * 2 + 1;
    char* result = (char*)malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    char* out = result;
    const char* cursor = input;
    regmatch_t pmatch[1];

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;

        for (size_t i = 0; i < match_start; ++i) {
            *out++ = tolower((unsigned char)cursor[i]);
        }

        if (cursor + match_start > input) {
            *out++ = '_';
        }

        *out++ = tolower((unsigned char)cursor[match_start]);
        cursor += pmatch[0].rm_eo;
    }

    while (*cursor != '\0') {
        *out++ = tolower((unsigned char)*cursor++);
    }

    *out = '\0';
    regfree(&regex);

    return result;
}

int main(void) {
    const char* test_cases[] = {
        "camelCaseString",
        "PascalCaseString",
        "already_snake_case",
        "simple",
        "",
        NULL
    };

    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; ++i) {
        if (test_cases[i] != NULL) {
            char* snake_case_str = convert_camel_to_snake(test_cases[i]);
            if (snake_case_str != NULL) {
                printf("%s\n", snake_case_str);
                free(snake_case_str);
            } else {
                fprintf(stderr, "Failed to convert string or allocate memory.\n");
            }
        }
    }

    return 0;
}