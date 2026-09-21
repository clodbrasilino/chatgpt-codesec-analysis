#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_to_decimal(const char *binary, uint64_t *decimal)
{
    uint64_t value = 0;

    if (binary == NULL || decimal == NULL || *binary == '\0') {
        return 0;
    }

    while (*binary != '\0') {
        unsigned int bit;

        if (*binary != '0' && *binary != '1') {
            return 0;
        }

        bit = (unsigned int)(*binary - '0');

        if (value > (UINT64_MAX - bit) / UINT64_C(2)) {
            return 0;
        }

        value = value * UINT64_C(2) + bit;
        ++binary;
    }

    *decimal = value;
    return 1;
}

static int read_binary(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input\n", stderr);
        } else {
            fputs("No input provided\n", stderr);
        }
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' &&
           buffer[length] != '\n' &&
           buffer[length] != '\r') {
        ++length;
    }

    if (buffer[length] == '\0' && !feof(stdin)) {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input\n", stderr);
            } else {
                fputs("Input is too long\n", stderr);
            }
            return 0;
        }

        if (ch == EOF && ferror(stdin)) {
            fputs("Failed to read input\n", stderr);
            return 0;
        }
    }

    buffer[length] = '\0';

    if (length == 0U) {
        fputs("No input provided\n", stderr);
        return 0;
    }

    return 1;
}

int main(void)
{
    enum { MAX_BINARY_DIGITS = 64 };
    char input[MAX_BINARY_DIGITS + 2U];
    uint64_t decimal;

    if (!read_binary(input, sizeof(input))) {
        return EXIT_FAILURE;
    }

    if (!binary_to_decimal(input, &decimal)) {
        fputs("Invalid or out-of-range binary number\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", decimal) < 0) {
        fputs("Failed to write output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}