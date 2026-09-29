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
    size_t rotations = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[4096];

    while (fgets(input, sizeof(input), stdin) != NULL) {
        size_t chunk_length = 0;
        int line_complete = 0;

        while (chunk_length < sizeof(input) && input[chunk_length] != '\0') {
            if (input[chunk_length] == '\n') {
                line_complete = 1;
                break;
            }
            ++chunk_length;
        }

        if (chunk_length > SIZE_MAX - length) {
            free(buffer);
            return EXIT_FAILURE;
        }

        size_t required = length + chunk_length;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            unsigned char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        for (size_t i = 0; i < chunk_length; ++i) {
            buffer[length + i] = (unsigned char)input[i];
        }
        length = required;

        if (line_complete) {
            break;
        }
    }

    if (ferror(stdin)) {
        free(buffer);
        return EXIT_FAILURE;
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