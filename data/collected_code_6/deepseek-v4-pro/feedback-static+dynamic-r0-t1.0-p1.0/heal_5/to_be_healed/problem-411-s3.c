#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  */

char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    size_t result_capacity = len + 1;
    char *result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;
    size_t input_index = 0;
    int capitalize_next = 0;
    int first_word = 1;

    while (input[input_index] != '\0') {
        char current = input[input_index];

        if (current == '_') {
            if (!first_word) {
                capitalize_next = 1;
            }
            input_index++;
            continue;
        }

        if (first_word) {
            result[result_index++] = (char)tolower((unsigned char)current);
            first_word = 0;
        } else if (capitalize_next) {
            result[result_index++] = (char)toupper((unsigned char)current);
            capitalize_next = 0;
        } else {
            result[result_index++] = (char)tolower((unsigned char)current);
        }

        input_index++;
    }

    result[result_index] = '\0';

    char *trimmed = realloc(result, result_index + 1);
    return trimmed ? trimmed : result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string",
        "alreadyCamel",
        "multiple__underscores",
        "_leading_underscore",
        "trailing_underscore_",
        "",
        "no_underscores_here",
        "a_b_c_d_e",
        "android_tv",
        "google_pixel",
        "apple_watch"
    };

    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *converted = snake_to_camel(test_cases[i]);
        if (converted != NULL) {
            printf("\"%s\" -> \"%s\"\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("\"%s\" -> NULL\n", test_cases[i]);
        }
    }

    return 0;
}