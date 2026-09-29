#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_flips(const char *str, size_t length, size_t *result)
{
    size_t flips_starting_with_zero = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }

        char expected = (i % 2U == 0U) ? '0' : '1';

        if (str[i] != expected) {
            ++flips_starting_with_zero;
        }
    }

    size_t flips_starting_with_one = length - flips_starting_with_zero;
    *result = flips_starting_with_zero < flips_starting_with_one
                  ? flips_starting_with_zero
                  : flips_starting_with_one;

    return 0;
}

int main(void)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *input = malloc(capacity);

    if (input == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity) {
            if (capacity > SIZE_MAX / 2U) {
                fputs("Input is too long.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2U;
            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                fputs("Memory allocation failed.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    size_t flips = 0U;

    if (minimum_flips(input, length, &flips) != 0) {
        fputs("Input must contain only binary characters.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", flips) < 0) {
        fputs("Failed to write output.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}