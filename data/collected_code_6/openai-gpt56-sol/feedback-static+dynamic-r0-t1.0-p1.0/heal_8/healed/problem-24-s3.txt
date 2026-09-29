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

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                return 0;
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
                    return 0;
                }
                break;
            }

            if (ch != '\n') {
                return 0;
            }

            break;
        }

        if (ch != '0' && ch != '1') {
            return 0;
        }

        if (digits >= 64) {
            return 0;
        }

        value = (value << 1) | (uint64_t)(ch - '0');
        ++digits;
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