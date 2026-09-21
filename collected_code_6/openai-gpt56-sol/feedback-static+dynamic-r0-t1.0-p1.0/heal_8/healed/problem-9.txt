#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_rotations(const unsigned char *str, size_t length,
                             size_t *result)
{
    size_t *prefix;
    size_t matched = 0;
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

    prefix = malloc(length * sizeof(*prefix));
    if (prefix == NULL) {
        return 0;
    }

    prefix[0] = 0;

    for (size_t i = 1; i < length; ++i) {
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
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t result = 0;
    int character;

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *resized;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                free(input);
                return EXIT_FAILURE;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length] = (unsigned char)character;
        ++length;
    }

    if (character == EOF && ferror(stdin)) {
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