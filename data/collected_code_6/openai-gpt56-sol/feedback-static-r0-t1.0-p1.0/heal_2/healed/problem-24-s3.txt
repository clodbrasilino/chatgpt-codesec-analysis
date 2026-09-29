#include <errno.h>
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

int main(void)
{
    enum { INPUT_SIZE = 128 };
    char input[INPUT_SIZE];
    uint64_t decimal;
    size_t length = 0;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("Failed to read input");
        } else {
            fputs("No input provided\n", stderr);
        }
        return EXIT_FAILURE;
    }

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != EOF && ch != '\n') {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n');

            if (ferror(stdin)) {
                perror("Failed to read input");
            } else {
                fputs("Binary number is too long\n", stderr);
            }
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            perror("Failed to read input");
            return EXIT_FAILURE;
        }
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    if (!binary_to_decimal(input, &decimal)) {
        fputs("Invalid or out-of-range binary number\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", decimal) < 0) {
        perror("Failed to write output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}