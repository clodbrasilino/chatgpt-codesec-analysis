#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_first_n_odds(uint64_t n, uint64_t *result)
{
    uint64_t square;

    if (result == NULL || n > UINT64_C(55108)) {
        return 0;
    }

    square = n * n;
    *result = square * (UINT64_C(2) * square - UINT64_C(1));
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;
    int ch;
    int digit_seen = 0;
    int trailing_space = 0;
    int overflow = 0;

    if (value == NULL) {
        return 0;
    }

    parsed = 0;

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n' && isspace((unsigned char)ch));

    if (ch == '+') {
        ch = fgetc(stdin);
    } else if (ch == '-') {
        while (ch != EOF && ch != '\n') {
            ch = fgetc(stdin);
        }
        return 0;
    }

    while (ch != EOF && ch != '\n') {
        if (isdigit((unsigned char)ch)) {
            unsigned int digit = (unsigned int)(ch - '0');

            if (trailing_space) {
                while (ch != EOF && ch != '\n') {
                    ch = fgetc(stdin);
                }
                return 0;
            }

            digit_seen = 1;

            if (parsed > (UINT64_MAX - digit) / UINTMAX_C(10)) {
                overflow = 1;
            } else if (!overflow) {
                parsed = parsed * UINTMAX_C(10) + digit;
            }
        } else if (isspace((unsigned char)ch)) {
            trailing_space = 1;
        } else {
            while (ch != EOF && ch != '\n') {
                ch = fgetc(stdin);
            }
            return 0;
        }

        ch = fgetc(stdin);
    }

    if (ferror(stdin) || !digit_seen || overflow) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    uint64_t value;
    uint64_t result;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum_first_n_odds(value, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}