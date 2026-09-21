#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static size_t minimum_rotations(const unsigned char *string, size_t length)
{
    size_t *prefix;
    size_t matched = 0;
    size_t period;

    if (string == NULL || length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*prefix)) {
        return length;
    }

    prefix = malloc(length * sizeof(*prefix));
    if (prefix == NULL) {
        return length;
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
    free(prefix);

    return length % period == 0 ? period : length;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

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

            resized = realloc(input, new_capacity);
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

    printf("%zu\n", minimum_rotations(input, length));
    free(input);

    return EXIT_SUCCESS;
}