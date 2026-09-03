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
    regmatch_t matches[3];
    const char *pattern = "([a-z0-9])([A-Z])";
    size_t input_len = strlen(input);
    size_t output_len = input_len + 1;
    char *output;
    char *out_ptr;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    const char *temp_cursor = input;
    while (regexec(&regex, temp_cursor, 3, matches, 0) == 0) {
        output_len++;
        temp_cursor += matches[0].rm_eo;
    }

    output = (char *)malloc(output_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    out_ptr = output;

    while (regexec(&regex, cursor, 3, matches, 0) == 0) {
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;

        if (match_start > 0) {
            memcpy(out_ptr, cursor, match_start);
            out_ptr += match_start;
        }

        *out_ptr++ = tolower((unsigned char)cursor[match_start]);
        *out_ptr++ = '_';
        *out_ptr++ = tolower((unsigned char)cursor[match_end - 1]);

        cursor += match_end;
    }

    while (*cursor) {
        *out_ptr++ = tolower((unsigned char)*cursor++);
    }
    *out_ptr = '\0';

    regfree(&regex);
    return output;
}

int main(void) {
    const char *tests[] = {
        "camelCase",
        "helloWorld",
        "thisIsATest",
        "already_snake",
        "mixedCase_WithSnake",
        "UPPERCASE",
        "camel123Case",
        "c",
        "chromeCast",
        "googleAssistant",
        "quadCore"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result != NULL) {
            printf("%s -> %s\n", tests[i], result);
            free(result);
        } else {
            printf("%s -> (conversion failed)\n", tests[i]);
        }
    }

    return 0;
}