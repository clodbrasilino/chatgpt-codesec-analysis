#include <stdio.h>
#include <stdlib.h>

static size_t minimum_rotations(const char *string, size_t length)
{
    size_t *prefix;
    size_t i;
    size_t period;
    size_t result;

    if (string == NULL || length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*prefix)) {
        return length;
    }

    prefix = calloc(length, sizeof(*prefix));
    if (prefix == NULL) {
        return length;
    }

    for (i = 1; i < length; ++i) {
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
    result = length % period == 0 ? period : length;

    free(prefix);
    return result;
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX) {
            free(buffer);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_buffer;

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

        buffer[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", minimum_rotations(buffer, length)) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}