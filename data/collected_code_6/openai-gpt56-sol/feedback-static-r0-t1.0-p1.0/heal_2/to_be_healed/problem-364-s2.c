#include <stdio.h>
#include <stdlib.h>

static int minimum_flips(const char *str, size_t length, size_t *result)
{
    size_t flips_starting_with_zero = 0;
    size_t flips_starting_with_one = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }

        char expected_zero = (i % 2U == 0U) ? '0' : '1';
        char expected_one = (i % 2U == 0U) ? '1' : '0';

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

    return 0;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
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

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (length == capacity) {
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

    size_t flips;

    if (minimum_flips(input, length, &flips) != 0) {
        fputs("Input must contain only binary characters.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    printf("%zu\n", flips);
    free(input);
    return EXIT_SUCCESS;
}