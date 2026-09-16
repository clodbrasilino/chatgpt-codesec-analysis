#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *input) {
    if (!input) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (!result) {
        return NULL;
    }

    size_t dst_idx = 0;
    int capitalize_next = 0;
    int first_char = 1;

    for (size_t i = 0; i < len; i++) {
        if (input[i] == '_') {
            capitalize_next = 1;
        } else {
            if (first_char) {
                if (input[i] >= 'A' && input[i] <= 'Z') {
                    result[dst_idx++] = input[i] + 32;
                } else {
                    result[dst_idx++] = input[i];
                }
                first_char = 0;
            } else if (capitalize_next) {
                result[dst_idx++] = toupper((unsigned char)input[i]);
            } else {
                result[dst_idx++] = input[i];
            }
            capitalize_next = 0;
        }
    }

    result[dst_idx] = '\0';
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
        "AndroidTv",
        "GooglePixel",
        "AppleWatch",
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