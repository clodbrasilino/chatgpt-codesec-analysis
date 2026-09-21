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
    int saw_terminator = 0;
    int ch;

    binary = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (binary == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            saw_terminator = 1;
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                goto cleanup;
            }
            if (next == EOF && ferror(stdin)) {
                goto cleanup;
            }

            saw_terminator = 1;
            break;
        }

        if (ch != '0' && ch != '1') {
            goto cleanup;
        }

        if (length >= (size_t)MAX_INPUT_LENGTH) {
            goto cleanup;
        }

        binary[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (length == 0) {
        goto cleanup;
    }

    if (saw_terminator) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch != EOF) {
            goto cleanup;
        }
        if (ferror(stdin)) {
            goto cleanup;
        }
    }

    binary[length] = '\0';

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