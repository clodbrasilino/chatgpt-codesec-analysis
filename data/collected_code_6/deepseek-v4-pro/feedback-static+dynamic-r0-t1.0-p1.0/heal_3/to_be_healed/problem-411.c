#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  */

char *snake_to_camel(const char *input) {
    if (!input) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (!result) {
        return NULL;
    }

    regex_t regex;
    const char *pattern = "_([a-z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }

    size_t dst_idx = 0;
    const char *cursor = input;
    int ret;
    regmatch_t matches[2];

    /* Possible weaknesses found:
     *  Although the value stored to 'ret' is used in the enclosing expression, the value is never actually read from 'ret' [deadcode.DeadStores]
     */
    while ((ret = regexec(&regex, cursor, 2, matches, 0)) == 0) {
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        size_t group_start = matches[1].rm_so;
        size_t group_end = matches[1].rm_eo;

        if (match_start > 0) {
            if (dst_idx + match_start > len) {
                break;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_idx, cursor, match_start);
            dst_idx += match_start;
        }

        if (group_end > group_start) {
            if (dst_idx >= len) {
                break;
            }
            result[dst_idx++] = (char)toupper((unsigned char)cursor[group_start]);
        }

        cursor += match_end;
    }

    size_t remaining = len - (cursor - input);
    if (remaining > 0) {
        if (dst_idx + remaining > len) {
            remaining = len - dst_idx;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_idx, cursor, remaining);
        dst_idx += remaining;
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