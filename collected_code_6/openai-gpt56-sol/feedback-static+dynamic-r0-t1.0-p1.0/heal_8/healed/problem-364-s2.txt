#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_flips(FILE *stream, size_t *result)
{
    size_t length = 0;
    size_t mismatches = 0;
    int ch;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF) {
        char expected;

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            ch = fgetc(stream);

            if (ch == '\n') {
                break;
            }

            if (ch == EOF) {
                if (ferror(stream)) {
                    return -1;
                }
                break;
            }

            return -1;
        }

        if (ch != '0' && ch != '1') {
            return -1;
        }

        if (length == SIZE_MAX) {
            return -1;
        }

        expected = (length & 1U) == 0U ? '0' : '1';

        if ((char)ch != expected) {
            ++mismatches;
        }

        ++length;
    }

    if (ferror(stream)) {
        return -1;
    }

    *result = mismatches < length - mismatches
                  ? mismatches
                  : length - mismatches;

    return 0;
}

int main(void)
{
    size_t flips;

    if (minimum_flips(stdin, &flips) != 0) {
        fputs("Invalid input or input error.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", flips) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}