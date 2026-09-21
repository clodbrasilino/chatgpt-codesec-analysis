#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_flips(const char *str, size_t length, size_t *result)
{
    size_t flips_starting_with_zero = 0U;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        char expected;

        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }

        expected = (i % 2U == 0U) ? '0' : '1';

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
    size_t flips_starting_with_zero = 0U;
    size_t length = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        char expected;

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                fputs("Input must contain only binary characters.\n", stderr);
                return EXIT_FAILURE;
            }

            if (next == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }

            ch = next;
            break;
        }

        if (ch != '0' && ch != '1') {
            fputs("Input must contain only binary characters.\n", stderr);
            return EXIT_FAILURE;
        }

        expected = (length % 2U == 0U) ? '0' : '1';

        if ((char)ch != expected) {
            ++flips_starting_with_zero;
        }

        if (length == SIZE_MAX) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        ++length;
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    {
        size_t flips;
        size_t flips_starting_with_one = length - flips_starting_with_zero;

        flips = flips_starting_with_zero < flips_starting_with_one
                    ? flips_starting_with_zero
                    : flips_starting_with_one;

        if (printf("%zu\n", flips) < 0) {
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}