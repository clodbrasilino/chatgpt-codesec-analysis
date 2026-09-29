#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char *snake_to_camel(const char *input) {
    if (!input) {
        return NULL;
    }

    size_t len = strlen(input);

    if (len == 0) {
        char *result = (char *)malloc(1);
        if (result) {
            result[0] = '\0';
        }
        return result;
    }

    size_t underscores = 0;
    for (size_t i = 0; i < len; i++) {
        if (input[i] == '_') {
            underscores++;
        }
    }

    size_t result_len = len - underscores;
    char *result = (char *)malloc(result_len + 1);
    if (!result) {
        return NULL;
    }

    size_t dst_idx = 0;
    size_t src_idx = 0;
    int capitalize_next = 0;
    int first_char = 1;

    while (src_idx < len) {
        if (input[src_idx] == '_') {
            capitalize_next = 1;
            src_idx++;
        } else if (first_char) {
            result[dst_idx] = (char)tolower((unsigned char)input[src_idx]);
            dst_idx++;
            first_char = 0;
            src_idx++;
        } else if (capitalize_next) {
            result[dst_idx] = (char)toupper((unsigned char)input[src_idx]);
            dst_idx++;
            capitalize_next = 0;
            src_idx++;
        } else {
            result[dst_idx] = (char)tolower((unsigned char)input[src_idx]);
            dst_idx++;
            src_idx++;
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
        "android_tv",
        "google_pixel",
        "apple_watch",
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