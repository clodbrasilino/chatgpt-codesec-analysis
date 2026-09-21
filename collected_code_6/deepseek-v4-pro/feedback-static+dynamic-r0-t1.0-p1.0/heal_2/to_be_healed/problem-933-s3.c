#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got <no output>
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  */

char *camel_to_snake(const char *input) {
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    if (input_len > SIZE_MAX / 2 - 1) {
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
                size_t to_copy = match_pos < remaining ? match_pos : remaining;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + length, input + pos, to_copy);
                length += to_copy;
                result[length] = '\0';
            }

            if (length > 0 && result[length - 1] != '_') {
                if (length + 1 < capacity) {
                    result[length] = '_';
                    length++;
                    result[length] = '\0';
                }
            }

            if (length + match_len >= capacity) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            for (size_t i = 0; i < match_len; i++) {
                char c = input[pos + match_pos + i];
                result[length + i] = c - 'A' + 'a';
            }
            length += match_len;
            result[length] = '\0';

            pos += match_pos + match_len;
        } else {
            size_t remaining = capacity - length - 1;
            size_t remaining_input = input_len - pos;
            size_t to_copy = remaining_input < remaining ? remaining_input : remaining;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + length, input + pos, to_copy);
            length += to_copy;
            result[length] = '\0';
            break;
        }
    }

    regfree(&regex);
    return result;
}

int main(int argc, char *argv[]) {
    const char *test_strings[] = {
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