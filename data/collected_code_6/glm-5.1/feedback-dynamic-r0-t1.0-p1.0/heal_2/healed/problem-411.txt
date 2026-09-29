#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (!snake_str) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    if (len == 0) {
        char *empty = malloc(1);
        if (!empty) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    char *result = malloc(len + 1);
    if (!result) {
        return NULL;
    }

    size_t src_idx = 0;
    size_t dst_idx = 0;

    while (src_idx < len) {
        if (snake_str[src_idx] == '_' && src_idx + 1 < len && islower((unsigned char)snake_str[src_idx + 1])) {
            result[dst_idx++] = toupper((unsigned char)snake_str[src_idx + 1]);
            src_idx += 2;
        } else {
            result[dst_idx++] = toupper((unsigned char)snake_str[src_idx++]);
        }
    }

    result[dst_idx] = '\0';

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "android_tv",
        "google_pixel",
        "apple_watch",
        "this_is_a_snake_case_string",
        "",
        NULL
    };

    for (int i = 0; i < 5; i++) {
        printf("Input: %s\n", test_cases[i] ? test_cases[i] : "NULL");
        char *output = snake_to_camel(test_cases[i]);
        if (output) {
            printf("Output: %s\n", output);
            free(output);
        } else {
            fprintf(stderr, "Conversion failed\n");
        }
    }

    return 0;
}