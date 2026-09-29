#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_flips(FILE *stream, size_t *result)
{
    size_t length = 0;
    size_t flips_starting_with_zero = 0;
    int ch;

    if (stream == NULL || result == NULL) {
        return 0;
    }

    while ((ch = fgetc(stream)) != EOF) {
        char expected;

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            ch = fgetc(stream);
            if (ch != '\n' && ch != EOF) {
                return 0;
            }
            break;
        }

        if (ch != '0' && ch != '1') {
            return 0;
        }

        if (length == SIZE_MAX) {
            return 0;
        }

        expected = (length % 2U == 0U) ? '0' : '1';
        if ((char)ch != expected) {
            ++flips_starting_with_zero;
        }

        ++length;
    }

    if (ferror(stream)) {
        return 0;
    }

    {
        size_t flips_starting_with_one = length - flips_starting_with_zero;
        *result = flips_starting_with_zero < flips_starting_with_one
                      ? flips_starting_with_zero
                      : flips_starting_with_one;
    }

    return 1;
}

int main(void)
{
    size_t flips;

    if (!minimum_flips(stdin, &flips)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", flips) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}