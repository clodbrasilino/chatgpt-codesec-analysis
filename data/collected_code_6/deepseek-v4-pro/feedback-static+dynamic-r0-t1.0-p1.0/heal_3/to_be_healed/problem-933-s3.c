#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got <no output>
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  */

static char *camel_to_snake(const char *input) {
    const char *pattern = "([A-Z])";
    regex_t regex;
    regmatch_t match;
    char *result = NULL;
    size_t capacity;
    size_t length = 0;
    size_t input_len;
    size_t pos = 0;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, SIZE_MAX);
    if (input_len == SIZE_MAX || input_len > SIZE_MAX / 2 - 1) {
        return NULL;
    }
    capacity = input_len * 2 + 1;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    result = (char *)malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    result[0] = '\0';

    while (pos < input_len) {
        if (regexec(&regex, input + pos, 1, &match, 0) == 0) {
            size_t match_pos = match.rm_so;
            size_t match_len = match.rm_eo - match.rm_so;

            if (match_pos > 0) {
                size_t remaining = capacity - length - 1;
                if (match_pos > remaining) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + length, input + pos, match_pos);
                length += match_pos;
                result[length] = '\0';
            }

            if (length > 0 && result[length - 1] != '_') {
                if (length + 2 > capacity) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result[length] = '_';
                length++;
                result[length] = '\0';
            }

            if (length + match_len >= capacity) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            for (size_t i = 0; i < match_len; i++) {
                char c = input[pos + match_pos + i];
                result[length + i] = (char)(c - 'A' + 'a');
            }
            length += match_len;
            result[length] = '\0';

            pos += match_pos + match_len;
        } else {
            size_t remaining = capacity - length - 1;
            size_t remaining_input = input_len - pos;
            if (remaining_input > remaining) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + length, input + pos, remaining_input);
            length += remaining_input;
            result[length] = '\0';
            break;
        }
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "google_assistant",
        "chrome_cast",
        "quad_core",
        "camelCaseString",
        "thisIsATest",
        "single",
        "",
        "ALLCAPS",
        "mixedCASEString"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *converted = camel_to_snake(test_strings[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", test_strings[i], converted);
            free(converted);
        } else {
            printf("%s -> (conversion failed)\n", test_strings[i]);
        }
    }

    return 0;
}