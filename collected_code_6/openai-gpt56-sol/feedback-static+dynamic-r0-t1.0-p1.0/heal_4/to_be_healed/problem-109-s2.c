#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };
    char *binary = NULL;
    size_t length = 0;
    size_t odd_rotations = 0;
    int status = EXIT_FAILURE;

    binary = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (binary == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(binary, MAX_INPUT_LENGTH + 1, stdin) == NULL) {
        goto cleanup;
    }

    while (binary[length] != '\0' &&
           binary[length] != '\n' &&
           binary[length] != '\r') {
        if (binary[length] != '0' && binary[length] != '1') {
            goto cleanup;
        }
        ++length;
    }

    if (length == 0) {
        goto cleanup;
    }

    if (binary[length] == '\0' && length == MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            goto cleanup;
        }

        if (ch == EOF && ferror(stdin)) {
            goto cleanup;
        }
    } else if (binary[length] == '\r') {
        if (binary[length + 1U] != '\n' &&
            binary[length + 1U] != '\0') {
            goto cleanup;
        }
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