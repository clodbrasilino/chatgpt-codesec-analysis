#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t src_idx = 0;
    size_t dest_idx = 0;
    int capitalize_next = 1;

    while (src_idx < len) {
        if (snake_str[src_idx] == '_') {
            capitalize_next = 1;
            src_idx++;
        } else {
            if (capitalize_next) {
                if (snake_str[src_idx] >= 'a' && snake_str[src_idx] <= 'z') {
                    camel_str[dest_idx++] = snake_str[src_idx] - 32;
                } else {
                    camel_str[dest_idx++] = snake_str[src_idx];
                }
                capitalize_next = 0;
            } else {
                camel_str[dest_idx++] = snake_str[src_idx];
            }
            src_idx++;
        }
    }

    camel_str[dest_idx] = '\0';
    return camel_str;
}

int main(void) {
    const char *test_cases[] = {
        "android_tv",
        "google_pixel",
        "apple_watch",
        "convert_this_snake_case_string"
    };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        char *output = snake_to_camel(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }

    return 0;
}