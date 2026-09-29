#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_flips(const char *str, size_t length, size_t *result)
{
    size_t flips_starting_with_zero = 0;

    if (result == NULL || (str == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        char expected = (i % 2U == 0U) ? '0' : '1';

        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }

        if (str[i] != expected) {
            ++flips_starting_with_zero;
        }
    }

    if (flips_starting_with_zero <= length / 2U) {
        *result = flips_starting_with_zero;
    } else {
        *result = length - flips_starting_with_zero;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    size_t flips = 0;
    int status = EXIT_FAILURE;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    fputs("Failed to read input.\n", stderr);
                    goto cleanup;
                }
                break;
            }

            if (next == '\n') {
                break;
            }

            fputs("Input must contain only binary characters.\n", stderr);
            goto cleanup;
        }

        if (ch != '0' && ch != '1') {
            fputs("Input must contain only binary characters.\n", stderr);
            goto cleanup;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    fputs("Input is too long.\n", stderr);
                    goto cleanup;
                }

                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length] = (char)ch;
        ++length;
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    if (minimum_flips(input, length, &flips) != 0) {
        fputs("Input must contain only binary characters.\n", stderr);
        goto cleanup;
    }

    if (printf("%zu\n", flips) < 0) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}