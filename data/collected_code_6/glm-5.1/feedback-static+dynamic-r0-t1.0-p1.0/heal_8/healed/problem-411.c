#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

size_t safe_strlen(const char *str) {
    if (!str) {
        return 0;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char *snake_to_camel(const char *snake_str) {
    if (!snake_str) {
        return NULL;
    }

    size_t len = safe_strlen(snake_str);
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

    if (snake_str[src_idx] >= 'a' && snake_str[src_idx] <= 'z') {
        result[dst_idx++] = snake_str[src_idx] - 32;
        src_idx++;
    }

    while (snake_str[src_idx] != '\0') {
        if (snake_str[src_idx] == '_') {
            if (snake_str[src_idx + 1] >= 'a' && snake_str[src_idx + 1] <= 'z') {
                result[dst_idx++] = snake_str[src_idx + 1] - 32;
                src_idx += 2;
            } else if (snake_str[src_idx + 1] != '\0') {
                result[dst_idx++] = snake_str[src_idx + 1];
                src_idx += 2;
            } else {
                src_idx++;
            }
        } else {
            result[dst_idx++] = snake_str[src_idx];
            src_idx++;
        }
    }

    result[dst_idx] = '\0';

    char *final_res = realloc(result, dst_idx + 1);
    if (final_res) {
        return final_res;
    }
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

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        if (test_cases[i] == NULL) continue;
        char *output = snake_to_camel(test_cases[i]);
        if (output) {
            printf("%s\n", output);
            free(output);
        } else {
            fprintf(stderr, "Conversion failed for: %s\n", test_cases[i]);
        }
    }

    return 0;
}