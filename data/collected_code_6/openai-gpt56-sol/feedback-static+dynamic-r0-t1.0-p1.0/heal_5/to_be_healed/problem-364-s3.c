#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_flips(const char *str, size_t length, size_t *result)
{
    size_t flips_starting_with_zero = 0;
    size_t flips_starting_with_one = 0;

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        char expected_zero = (i % 2U == 0U) ? '0' : '1';
        char expected_one = (i % 2U == 0U) ? '1' : '0';

        if (str[i] != '0' && str[i] != '1') {
            return 0;
        }

        if (str[i] != expected_zero) {
            ++flips_starting_with_zero;
        }

        if (str[i] != expected_one) {
            ++flips_starting_with_one;
        }
    }

    *result = flips_starting_with_zero < flips_starting_with_one
                  ? flips_starting_with_zero
                  : flips_starting_with_one;

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t flips = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (length == 0U) {
        static const char empty_input[] = "";
        if (!minimum_flips(empty_input, 0U, &flips)) {
            goto cleanup;
        }
    } else if (!minimum_flips(input, length, &flips)) {
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