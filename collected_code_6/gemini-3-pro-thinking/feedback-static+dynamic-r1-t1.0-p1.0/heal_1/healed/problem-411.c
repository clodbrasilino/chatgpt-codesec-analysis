#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int capitalize_next = 1;

    while (snake_str[i] != '\0') {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                result[j++] = (char)toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                result[j++] = snake_str[i];
            }
        }
        i++;
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *test_strings[] = {
        "hello_world",
        "this_is_a_test",
        "alreadyCamel",
        "multiple__underscores",
        "_leading_underscore",
        "trailing_underscore_",
        "android_tv",
        "google_pixel",
        "apple_watch",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; ++i) {
        char *camel = snake_to_camel(test_strings[i]);
        if (camel != NULL) {
            printf("%s\n", camel);
            free(camel);
        } else {
            fprintf(stderr, "Conversion failed for input at index %zu\n", i);
        }
    }

    return EXIT_SUCCESS;
}