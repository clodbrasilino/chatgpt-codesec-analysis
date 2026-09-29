#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_rotations(const char *str, size_t length, size_t *result)
{
    size_t *prefix;
    size_t i;
    size_t matched;
    size_t period;

    if (result == NULL || (str == NULL && length != 0)) {
        return 0;
    }

    if (length == 0) {
        *result = 0;
        return 1;
    }

    if (length > SIZE_MAX / sizeof(*prefix)) {
        return 0;
    }

    prefix = calloc(length, sizeof(*prefix));
    if (prefix == NULL) {
        return 0;
    }

    for (i = 1, matched = 0; i < length; ++i) {
        while (matched > 0 && str[i] != str[matched]) {
            matched = prefix[matched - 1];
        }

        if (str[i] == str[matched]) {
            ++matched;
        }

        prefix[i] = matched;
    }

    period = length - prefix[length - 1];
    if (length % period != 0) {
        period = length;
    }

    free(prefix);
    *result = period;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t result;
    int character;

    for (;;) {
        character = getchar();

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (!minimum_rotations(input, length, &result)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", result) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}