#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

static int minimum_rotations(const char *str, size_t length, size_t *result)
{
    size_t *prefix;
    size_t i;
    size_t matched;
    size_t period;

    if (str == NULL || result == NULL) {
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

    matched = 0;
    for (i = 1; i < length; ++i) {
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
    size_t rotations;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        if (length == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
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

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
        capacity = 1;
    }

    if (length >= capacity) {
        char *resized;

        if (length == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        resized = realloc(input, length + 1);
        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';

    if (!minimum_rotations(input, length, &rotations)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", rotations) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}