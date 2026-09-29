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
        char expected = ((i & 1U) == 0U) ? '0' : '1';

        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }

        if (str[i] != expected) {
            ++flips_starting_with_zero;
        }
    }

    {
        size_t flips_starting_with_one = length - flips_starting_with_zero;
        *result = flips_starting_with_zero < flips_starting_with_one
                    ? flips_starting_with_zero
                    : flips_starting_with_one;
    }

    return 0;
}

int main(void)
{
    size_t length = 0;
    size_t mismatches = 0;
    size_t flips;
    int ch;

    while ((ch = getchar()) != EOF) {
        char expected;

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = getchar();

            if (next == EOF) {
                if (ferror(stdin)) {
                    fputs("Failed to read input.\n", stderr);
                    return EXIT_FAILURE;
                }
                break;
            }

            if (next == '\n') {
                break;
            }

            fputs("Input must contain only binary characters.\n", stderr);
            return EXIT_FAILURE;
        }

        if (ch != '0' && ch != '1') {
            fputs("Input must contain only binary characters.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length == SIZE_MAX) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        expected = ((length & 1U) == 0U) ? '0' : '1';
        if ((char)ch != expected) {
            ++mismatches;
        }

        ++length;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    flips = mismatches < length - mismatches
                ? mismatches
                : length - mismatches;

    if (printf("%zu\n", flips) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}