#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_rotations(const unsigned char *string, size_t length,
                             size_t *result)
{
    size_t *prefix;
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

    for (size_t i = 1; i < length; ++i) {
        size_t matched = prefix[i - 1];

        while (matched > 0 && string[i] != string[matched]) {
            matched = prefix[matched - 1];
        }

        if (string[i] == string[matched]) {
            ++matched;
        }

        prefix[i] = matched;
    }

    period = length - prefix[length - 1];
    *result = (length % period == 0) ? period : length;

    free(prefix);
    return 0;
}

int main(void)
{
    unsigned char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t rotations;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_buffer;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (unsigned char)character;
    }

    if (minimum_rotations(buffer, length, &rotations) != 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", rotations) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}