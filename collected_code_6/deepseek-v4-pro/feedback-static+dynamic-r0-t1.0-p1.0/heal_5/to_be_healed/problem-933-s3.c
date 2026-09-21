#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static bool is_uppercase(char c) {
    return (c >= 'A' && c <= 'Z');
}

static char to_lowercase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return (char)(c + ('a' - 'A'));
    }
    return c;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got <no output>
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  */

static char *camel_to_snake(const char *input) {
    size_t input_len;
    size_t capacity;
    char *result;
    size_t length = 0;
    size_t pos = 0;
    size_t segment_start;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, SIZE_MAX / 2 - 1);
    if (input_len >= SIZE_MAX / 2 - 1) {
        return NULL;
    }

    capacity = input_len * 2 + 1;
    result = (char *)malloc(capacity);
    if (result == NULL) {
        return NULL;
    }

    segment_start = 0;

    for (pos = 0; pos < input_len; pos++) {
        if (is_uppercase(input[pos])) {
            if (pos > segment_start) {
                size_t segment_len = pos - segment_start;
                if (length + segment_len + 1 > capacity) {
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + length, input + segment_start, segment_len);
                length += segment_len;
            }

            if (length > 0 && result[length - 1] != '_') {
                if (length + 1 >= capacity) {
                    free(result);
                    return NULL;
                }
                result[length] = '_';
                length++;
            }

            if (length + 1 > capacity) {
                free(result);
                return NULL;
            }
            result[length] = to_lowercase(input[pos]);
            length++;

            segment_start = pos + 1;
        }
    }

    if (segment_start < input_len) {
        size_t remaining = input_len - segment_start;
        if (length + remaining + 1 > capacity) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + length, input + segment_start, remaining);
        length += remaining;
    }

    result[length] = '\0';
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "googleAssistant",
        "chromeCast",
        "quadCore",
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