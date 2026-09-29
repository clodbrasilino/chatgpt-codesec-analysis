#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t dest_idx = 0;
    int capitalize_next = 1;

    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel_str[dest_idx++] = (char)toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                camel_str[dest_idx++] = snake_str[i];
            }
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
        "convert_this_snake_case_string",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *output = snake_to_camel(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }

    return 0;
}