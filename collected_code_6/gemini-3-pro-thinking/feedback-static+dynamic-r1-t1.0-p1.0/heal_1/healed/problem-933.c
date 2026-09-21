#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    size_t max_len = (len * 2) + 1;
    char *result = (char *)malloc(max_len * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (i > 0 && isupper(c)) {
            unsigned char prev = (unsigned char)input[i - 1];
            if (islower(prev) || isdigit(prev)) {
                result[j++] = '_';
            }
        }
        result[j++] = (char)tolower(c);
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "googleAssistant",
        "chromeCast",
        "quadCore",
        "camelCase",
        "thisIsATest",
        "already_snake_case",
        "convert123ToSnake",
        "SimpleTest",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; ++i) {
        char *snake = camel_to_snake(test_cases[i]);
        if (snake != NULL) {
            printf("%s -> %s\n", test_cases[i], snake);
            free(snake);
        } else {
            fprintf(stderr, "Failed to convert %s\n", test_cases[i]);
        }
    }

    return 0;
}