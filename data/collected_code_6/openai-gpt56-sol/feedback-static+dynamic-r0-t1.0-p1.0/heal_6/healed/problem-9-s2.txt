#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_rotations(const unsigned char *string, size_t length,
                             size_t *result)
{
    size_t *prefix;
    size_t matched = 0;
    size_t period;

    if (result == NULL) {
        return -1;
    }

    if (length == 0) {
        *result = 0;
        return 0;
    }

    if (string == NULL || length > SIZE_MAX / sizeof(*prefix)) {
        return -1;
    }

    prefix = malloc(length * sizeof(*prefix));
    if (prefix == NULL) {
        return -1;
    }

    prefix[0] = 0;

    for (size_t index = 1; index < length; ++index) {
        while (matched > 0 && string[index] != string[matched]) {
            matched = prefix[matched - 1];
        }

        if (string[index] == string[matched]) {
            ++matched;
        }

        prefix[index] = matched;
    }

    period = length - prefix[length - 1];
    *result = (length % period == 0) ? period : length;

    free(prefix);
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t result = 0;
    int character = 0;

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

            if (new_capacity > SIZE_MAX / sizeof(*input)) {
                free(input);
                return EXIT_FAILURE;
            }

            resized = realloc(input, new_capacity * sizeof(*input));
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (minimum_rotations(input, length, &result) != 0) {
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