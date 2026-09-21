#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_flips(const char *str, size_t length, size_t *result)
{
    size_t flips_starting_with_zero = 0;

    if (str == NULL || result == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        const char expected = (i & 1U) == 0U ? '0' : '1';

        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }

        if (str[i] != expected) {
            ++flips_starting_with_zero;
        }
    }

    {
        const size_t flips_starting_with_one =
            length - flips_starting_with_zero;
        *result = flips_starting_with_zero < flips_starting_with_one
                    ? flips_starting_with_zero
                    : flips_starting_with_one;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t flips = 0;
    int status = EXIT_FAILURE;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        char *resized;
        size_t new_capacity;

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            const int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                goto cleanup;
            }

            if (next == EOF && ferror(stdin)) {
                goto cleanup;
            }

            break;
        }

        if (ch != '0' && ch != '1') {
            goto cleanup;
        }

        if (length == SIZE_MAX) {
            goto cleanup;
        }

        if (length < capacity) {
            input[length++] = (char)ch;
            continue;
        }

        if (capacity == 0) {
            new_capacity = 64;
        } else {
            if (capacity > SIZE_MAX / 2) {
                goto cleanup;
            }
            new_capacity = capacity * 2;
        }

        if (new_capacity <= length) {
            goto cleanup;
        }

        resized = realloc(input, new_capacity);
        if (resized == NULL) {
            goto cleanup;
        }

        input = resized;
        capacity = new_capacity;
        input[length++] = (char)ch;
    }

    if (ferror(stdin) || length == 0) {
        goto cleanup;
    }

    if (minimum_flips(input, length, &flips) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", flips) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}