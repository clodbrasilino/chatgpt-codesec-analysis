#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LEN 1024

char *snake_to_camel(const char *input) {
    char *result = NULL;
    size_t i = 0;
    size_t j = 0;
    size_t len;
    int capitalize_next = 0;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);
    if (len == 0 || len >= MAX_STRING_LEN) {
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (input[0] >= 'a' && input[0] <= 'z') {
        result[j++] = (char)toupper((unsigned char)input[0]);
        i = 1;
    }

    for (; i < len; i++) {
        if (input[i] == '_') {
            if (i + 1 < len && input[i + 1] >= 'a' && input[i + 1] <= 'z') {
                capitalize_next = 1;
            } else {
                result[j++] = input[i];
            }
        } else {
            if (capitalize_next && input[i] >= 'a' && input[i] <= 'z') {
                result[j++] = (char)toupper((unsigned char)input[i]);
                capitalize_next = 0;
            } else {
                result[j++] = input[i];
            }
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string_example",
        "single",
        "multiple__underscores",
        "google_pixel",
        "apple_watch",
        "android_tv",
        NULL
    };
    int i;

    for (i = 0; test_cases[i] != NULL; i++) {
        char *camel = snake_to_camel(test_cases[i]);
        if (camel != NULL) {
            printf("Input:  %s\n", test_cases[i]);
            printf("Output: %s\n\n", camel);
            free(camel);
        } else {
            printf("Conversion failed for: %s\n\n", test_cases[i]);
        }
    }

    return 0;
}