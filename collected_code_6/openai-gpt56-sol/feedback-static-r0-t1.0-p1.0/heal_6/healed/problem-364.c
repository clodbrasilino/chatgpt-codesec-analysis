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
        char expected = (i % 2U == 0U) ? '0' : '1';

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
    size_t flips_starting_with_zero = 0;
    size_t result;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        char expected;

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                return EXIT_FAILURE;
            }

            if (next == EOF && ferror(stdin)) {
                return EXIT_FAILURE;
            }

            break;
        }

        if (ch != '0' && ch != '1') {
            return EXIT_FAILURE;
        }

        if (length == SIZE_MAX) {
            return EXIT_FAILURE;
        }

        expected = (length % 2U == 0U) ? '0' : '1';
        if ((char)ch != expected) {
            ++flips_starting_with_zero;
        }

        ++length;
    }

    if (ferror(stdin) || length == 0) {
        return EXIT_FAILURE;
    }

    {
        size_t flips_starting_with_one = length - flips_starting_with_zero;
        result = flips_starting_with_zero < flips_starting_with_one
                    ? flips_starting_with_zero
                    : flips_starting_with_one;
    }

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}