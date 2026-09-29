#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t sum;
    uint64_t square;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    sum = a * b;

    if (sum != 0 && sum > UINT64_MAX / sum) {
        return 0;
    }

    square = sum * sum;

    if (square < sum) {
        return 0;
    }

    *result = square - sum;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uint64_t number = 0;
    int ch;
    int have_digit = 0;
    int trailing_space = 0;

    if (value == NULL) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch == ' ' || ch == '\t' || ch == '\r' ||
             ch == '\f' || ch == '\v');

    while (ch != '\n' && ch != EOF) {
        if (ch >= '0' && ch <= '9' && !trailing_space) {
            uint64_t digit = (uint64_t)(ch - '0');

            if (number > (UINT64_MAX - digit) / UINT64_C(10)) {
                do {
                    ch = fgetc(stdin);
                } while (ch != '\n' && ch != EOF);
                return 0;
            }

            number = number * UINT64_C(10) + digit;
            have_digit = 1;
        } else if (have_digit &&
                   (ch == ' ' || ch == '\t' || ch == '\r' ||
                    ch == '\f' || ch == '\v')) {
            trailing_space = 1;
        } else {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
            return 0;
        }

        ch = fgetc(stdin);
    }

    if (!have_digit || ferror(stdin)) {
        return 0;
    }

    *value = number;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t difference;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(n, &difference)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}