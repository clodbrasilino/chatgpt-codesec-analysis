#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_rotations(const unsigned char *string, size_t length,
                             size_t *result)
{
    size_t *prefix;
    size_t i;
    size_t period;

    if (result == NULL) {
        return 0;
    }

    if (length == 0) {
        *result = 0;
        return 1;
    }

    if (string == NULL || length > SIZE_MAX / sizeof(*prefix)) {
        return 0;
    }

    prefix = malloc(length * sizeof(*prefix));
    if (prefix == NULL) {
        return 0;
    }

    prefix[0] = 0;

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
    *result = length % period == 0 ? period : length;

    free(prefix);
    return 1;
}

static int read_line(FILE *stream, unsigned char **buffer, size_t *length)
{
    unsigned char *data = NULL;
    size_t capacity = 0;
    size_t used = 0;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(data);
                return 0;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (used == capacity) {
            size_t new_capacity;
            unsigned char *new_data;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(data);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= used) {
                free(data);
                return 0;
            }

            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[used++] = (unsigned char)character;
    }

    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    unsigned char *buffer = NULL;
    size_t length = 0;
    size_t rotations;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &buffer, &length)) {
        goto cleanup;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    if (!minimum_rotations(buffer, length, &rotations)) {
        goto cleanup;
    }

    if (printf("%zu\n", rotations) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(buffer);
    return status;
}