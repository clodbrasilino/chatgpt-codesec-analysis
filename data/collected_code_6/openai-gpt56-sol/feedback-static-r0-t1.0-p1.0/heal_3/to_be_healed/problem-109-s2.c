#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_odd_rotations(const char *binary, size_t length, size_t *count)
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
    char *binary = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t odd_rotations = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            continue;
        }

        if (ch != '0' && ch != '1') {
            goto cleanup;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_binary;

            if (capacity == 0) {
                new_capacity = 16;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*binary)) {
                goto cleanup;
            }

            new_binary = realloc(binary, new_capacity * sizeof(*binary));
            if (new_binary == NULL) {
                goto cleanup;
            }

            binary = new_binary;
            capacity = new_capacity;
        }

        binary[length++] = (char)ch;
    }

    if (length == 0) {
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