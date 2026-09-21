#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_to_decimal_stream(FILE *stream, uint64_t *decimal)
{
    uint64_t value = 0;
    size_t digits = 0;
    int ch;

    if (stream == NULL || decimal == NULL) {
        return 0;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        uint64_t bit;

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                return 0;
            }

            if (next == EOF && ferror(stream)) {
                return 0;
            }

            ch = next;
            break;
        }

        if (ch != '0' && ch != '1') {
            return 0;
        }

        bit = (uint64_t)(ch - '0');

        if (value > (UINT64_MAX - bit) / UINT64_C(2)) {
            return 0;
        }

        value = value * UINT64_C(2) + bit;
        ++digits;
    }

    if (ch == EOF && ferror(stream)) {
        return 0;
    }

    if (digits == 0) {
        return 0;
    }

    *decimal = value;
    return 1;
}

int main(void)
{
    uint64_t decimal;

    if (!binary_to_decimal_stream(stdin, &decimal)) {
        if (ferror(stdin)) {
            perror("Failed to read input");
        } else {
            fputs("Invalid or out-of-range binary number\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", decimal) < 0) {
        perror("Failed to write output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}