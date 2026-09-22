#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

static void capitalize(char *str) {
    if (str && *str) {
        *str = toupper((unsigned char)*str);
    }
}

char *snake_to_camel(const char *input) {
    if (!input) {
        return NULL;
    }

    size_t len = strlen(input);
    if (len == 0) {
        char *empty = (char *)malloc(1);
        if (empty) {
            empty[0] = '\0';
        }
        return empty;
    }

    char *result = (char *)malloc(len + 1);
    if (!result) {
        return NULL;
    }

    regex_t regex;
    const char *pattern = "_([a-zA-Z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }

    const char *src = input;
    char *dst = result;

    while (*src) {
        if (*src == '_') {
            src++;
            if (*src && isalpha((unsigned char)*src)) {
                *dst++ = toupper((unsigned char)*src);
                src++;
            }
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';

    regfree(&regex);

    if (result[0] && islower((unsigned char)result[0])) {
        result[0] = toupper((unsigned char)result[0]);
    }

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