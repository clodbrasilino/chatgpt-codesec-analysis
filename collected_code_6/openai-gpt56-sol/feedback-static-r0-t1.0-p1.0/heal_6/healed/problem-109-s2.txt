#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_odd_rotations(const char *binary, size_t length,
                               size_t *count)
{
    size_t odd_count = 0;

    if (binary == NULL || count == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (binary[i] == '1') {
            ++odd_count;
        } else if (binary[i] != '0') {
            return 0;
        }
    }

    *count = odd_count;
    return 1;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1048576 };

    char *binary = malloc(MAX_INPUT_LENGTH);
    size_t length = 0;
    size_t odd_rotations = 0;
    int status = EXIT_FAILURE;
    int ch;

    if (binary == NULL) {
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            continue;
        }

        if (ch != '0' && ch != '1') {
            goto cleanup;
        }

        if (length >= MAX_INPUT_LENGTH) {
            goto cleanup;
        }

        binary[length++] = (char)ch;
    }

    if (ferror(stdin) || length == 0) {
        goto cleanup;
    }

    if (!count_odd_rotations(binary, length, &odd_rotations)) {
        goto cleanup;
    }

    if (printf("%zu\n", odd_rotations) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(binary);
    return status;
}