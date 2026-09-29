#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    int capitalize_next = 0;

    if (input[0] == '_') {
        capitalize_next = 1;
        src_pos = 1;
    }

    for (; src_pos < len; src_pos++) {
        if (input[src_pos] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                result[dst_pos++] = toupper((unsigned char)input[src_pos]);
                capitalize_next = 0;
            } else {
                result[dst_pos++] = input[src_pos];
            }
        }
    }

    result[dst_pos] = '\0';
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "android_tv",
        "google_pixel",
        "apple_watch",
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "alreadyCamel",
        "multiple__underscores",
        "_leading_underscore",
        "trailing_underscore_",
        "with_1_number_2",
        "",
        "a",
        "_",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = snake_to_camel(test_cases[i]);
        if (converted != NULL) {
            printf("\"%s\" -> \"%s\"\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("\"%s\" -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}