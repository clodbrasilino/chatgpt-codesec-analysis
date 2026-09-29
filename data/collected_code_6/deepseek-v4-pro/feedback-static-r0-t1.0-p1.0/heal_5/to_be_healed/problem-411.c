#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *input) {
    if (!input) {
        return NULL;
    }

    size_t len = strnlen(input, 4096);
    if (len == 0) {
        char *empty = (char *)malloc(1);
        if (empty) {
            empty[0] = '\0';
        }
        return empty;
    }

    size_t result_size = len + 1;
    char *result = (char *)malloc(result_size);
    if (!result) {
        return NULL;
    }

    regex_t regex;
    const char *pattern = "_([a-z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }

    regmatch_t matches[2];
    size_t dst_idx = 0;
    const char *cursor = input;
    size_t remaining = len;

    while (remaining > 0 && regexec(&regex, cursor, 2, matches, 0) == 0) {
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        size_t group_start = matches[1].rm_so;

        if (match_start > 0) {
            if (dst_idx + match_start > result_size - 1) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_idx, cursor, match_start);
            dst_idx += match_start;
        }

        if (dst_idx < result_size - 1) {
            result[dst_idx] = (char)toupper((unsigned char)cursor[group_start]);
            dst_idx++;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t advance = match_end;
        if (advance == 0) {
            advance = 1;
        }
        cursor += advance;
        remaining -= advance;
    }

    if (remaining > 0) {
        if (dst_idx + remaining > result_size - 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_idx, cursor, remaining);
        dst_idx += remaining;
    }

    if (dst_idx >= result_size) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    result[dst_idx] = '\0';
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "already_camel",
        "multiple__underscores",
        "_leading_underscore",
        "trailing_underscore_",
        "numbers_123_test",
        "all_lower_case",
        "",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = snake_to_camel(test_cases[i]);
        if (converted) {
            printf("%s -> %s\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("%s -> NULL\n", test_cases[i]);
        }
    }

    return 0;
}