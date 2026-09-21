#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_flips_stream(FILE *stream, size_t *result)
{
    size_t length = 0;
    size_t flips_starting_with_zero = 0;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            ch = fgetc(stream);

            if (ch == EOF) {
                if (ferror(stream)) {
                    return -1;
                }
                break;
            }

            if (ch != '\n') {
                return -1;
            }

            break;
        }

        if (ch != '0' && ch != '1') {
            return -1;
        }

        if (length == SIZE_MAX) {
            return -1;
        }

        if (ch != ((length & 1U) == 0U ? '0' : '1')) {
            ++flips_starting_with_zero;
        }

        ++length;
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
    size_t flips;

    if (minimum_flips_stream(stdin, &flips) != 0) {
        fputs("Invalid input or input read failure.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", flips) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}