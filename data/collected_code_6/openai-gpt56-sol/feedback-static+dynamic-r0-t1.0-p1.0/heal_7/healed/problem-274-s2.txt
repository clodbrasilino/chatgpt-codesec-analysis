#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_index_binomial_coefficients(uint32_t n, uint64_t *result)
{
    if (result == NULL || n > 64U) {
        return -1;
    }

    *result = n == 0U
        ? UINT64_C(1)
        : UINT64_C(1) << (n - 1U);

    return 0;
}

static int read_value(uint32_t *result)
{
    uintmax_t value = 0;
    int ch;
    int saw_digit = 0;

    if (result == NULL) {
        return -1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n' && isspace((unsigned char)ch));

    while (ch != EOF && ch != '\n' && isdigit((unsigned char)ch)) {
        unsigned int digit = (unsigned int)(ch - '0');

        saw_digit = 1;

        if (value > (UINT32_MAX - digit) / 10U) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && ch != '\n');
            return -1;
        }

        value = value * 10U + digit;
        ch = fgetc(stdin);
    }

    while (ch != EOF && ch != '\n' && isspace((unsigned char)ch)) {
        ch = fgetc(stdin);
    }

    if (!saw_digit || (ch != EOF && ch != '\n')) {
        while (ch != EOF && ch != '\n') {
            ch = fgetc(stdin);
        }
        return -1;
    }

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    *result = (uint32_t)value;
    return 0;
}

int main(void)
{
    uint32_t value;
    uint64_t sum;

    if (read_value(&value) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_even_index_binomial_coefficients(value, &sum) != 0) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}