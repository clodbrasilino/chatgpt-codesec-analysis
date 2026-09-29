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
        uint64_t bit;

        if (*binary != '0' && *binary != '1') {
            return 0;
        }

        bit = (uint64_t)(*binary - '0');

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
    char input[65];
    size_t length = 0;
    uint64_t decimal;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length >= sizeof(input) - 1) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stdin)) {
                perror("Failed to read input");
            } else {
                fputs("Input is too long\n", stderr);
            }

            return EXIT_FAILURE;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        perror("Failed to read input");
        return EXIT_FAILURE;
    }

    if (length == 0) {
        fputs("No input provided\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

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