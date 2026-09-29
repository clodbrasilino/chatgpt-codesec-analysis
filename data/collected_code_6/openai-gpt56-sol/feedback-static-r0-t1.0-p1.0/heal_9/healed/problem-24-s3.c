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

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return !(ch == EOF && ferror(stdin));
}

static int read_binary(char **input)
{
    enum { MAX_BINARY_DIGITS = 64 };
    char *buffer;
    size_t length = 0;

    if (input == NULL) {
        return 0;
    }

    *input = NULL;
    buffer = malloc(MAX_BINARY_DIGITS + 1U);
    if (buffer == NULL) {
        fputs("Failed to allocate input buffer\n", stderr);
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input\n", stderr);
                free(buffer);
                return 0;
            }
            break;
        }

        if (length == MAX_BINARY_DIGITS) {
            if (!discard_line()) {
                fputs("Failed to read input\n", stderr);
            } else {
                fputs("Input is too long\n", stderr);
            }
            free(buffer);
            return 0;
        }

        buffer[length++] = (char)ch;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    if (length == 0) {
        fputs("No input provided\n", stderr);
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *input = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    uint64_t decimal;

    if (!read_binary(&input)) {
        return EXIT_FAILURE;
    }

    if (!binary_to_decimal(input, &decimal)) {
        fputs("Invalid or out-of-range binary number\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", decimal) < 0) {
        fputs("Failed to write output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}