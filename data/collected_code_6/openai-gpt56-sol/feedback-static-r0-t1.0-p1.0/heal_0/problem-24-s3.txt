#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int binary_to_decimal(const char *binary, uint64_t *decimal)
{
    uint64_t value = 0;
    const unsigned char *p = (const unsigned char *)binary;

    if (binary == NULL || decimal == NULL || *p == '\0') {
        return 0;
    }

    while (*p != '\0') {
        uint64_t bit;

        if (*p != '0' && *p != '1') {
            return 0;
        }

        bit = (uint64_t)(*p - (unsigned char)'0');

        if (value > (UINT64_MAX - bit) / UINT64_C(2)) {
            return 0;
        }

        value = value * UINT64_C(2) + bit;
        ++p;
    }

    *decimal = value;
    return 1;
}

int main(void)
{
    char input[128];
    uint64_t decimal;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("Failed to read input");
        } else {
            fputs("No input provided\n", stderr);
        }
        return EXIT_FAILURE;
    }

    {
        size_t length = 0;

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] == '\n') {
            input[length] = '\0';
        } else if (!feof(stdin)) {
            int ch;

            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stdin)) {
                perror("Failed to read input");
            } else {
                fputs("Binary number is too long\n", stderr);
            }
            return EXIT_FAILURE;
        }
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