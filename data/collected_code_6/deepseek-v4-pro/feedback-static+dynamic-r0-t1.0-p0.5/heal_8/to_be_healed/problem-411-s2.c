#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  */

static char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len == 0) {
        char *result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t max_result_len = len + 1;
    char *result = malloc(max_result_len);
    if (result == NULL) {
        return NULL;
    }

    size_t dst_pos = 0;
    int capitalize_next = 0;
    int first_char = 1;

    for (size_t i = 0; i < len; i++) {
        char c = input[i];

        if (c == '_') {
            if (!first_char) {
                capitalize_next = 1;
            }
            continue;
        }

        if (dst_pos >= max_result_len - 1) {
            free(result);
            return NULL;
        }

        if (first_char) {
            result[dst_pos++] = (char)tolower((unsigned char)c);
            first_char = 0;
        } else if (capitalize_next) {
            result[dst_pos++] = (char)toupper((unsigned char)c);
            capitalize_next = 0;
        } else {
            result[dst_pos++] = c;
        }
    }

    result[dst_pos] = '\0';

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "alreadycamel",
        "multiple__underscores",
        "_leading_underscore",
        "trailing_underscore_",
        "android_tv",
        "google_pixel",
        "apple_watch",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = snake_to_camel(test_cases[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("%s -> conversion failed\n", test_cases[i]);
        }
    }

    return 0;
}