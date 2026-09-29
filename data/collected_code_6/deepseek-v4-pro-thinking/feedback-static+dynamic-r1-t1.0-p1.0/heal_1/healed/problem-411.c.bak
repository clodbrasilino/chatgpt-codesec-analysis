#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *output = malloc(len + 1);
    if (output == NULL) {
        return NULL;
    }

    int capitalize = 1;
    char *dest = output;

    for (const char *src = input; *src != '\0'; ++src) {
        if (*src == '_') {
            capitalize = 1;
            continue;
        }
        if (capitalize && isalpha((unsigned char)*src)) {
            *dest++ = (char)toupper((unsigned char)*src);
            capitalize = 0;
        } else {
            *dest++ = *src;
            capitalize = 0;
        }
    }
    *dest = '\0';

    return output;
}

int main(void)
{
    const char *test_cases[] = {
        "android_tv",
        "google_pixel",
        "apple_watch"
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        char *result = snake_to_camel(test_cases[i]);
        if (result == NULL) {
            fprintf(stderr, "Conversion failed for %s\n", test_cases[i]);
            return EXIT_FAILURE;
        }
        printf("%s\n", result);
        free(result);
    }

    return EXIT_SUCCESS;
}