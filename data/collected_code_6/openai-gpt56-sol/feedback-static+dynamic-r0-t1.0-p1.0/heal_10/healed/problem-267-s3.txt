#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int sum_odd_squares(uint64_t n, uint64_t *result)
{
    const uint64_t limit = UINT64_C(1903309);
    uint64_t a;
    uint64_t b;
    uint64_t c;

    if (result == NULL || n > limit) {
        return 0;
    }

    a = n;
    b = UINT64_C(2) * n - UINT64_C(1);
    c = UINT64_C(2) * n + UINT64_C(1);

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    a *= b;

    if (c != 0 && a > UINT64_MAX / c) {
        return 0;
    }

    *result = a * c;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;
    int ch;
    int digit_seen = 0;

    if (value == NULL) {
        return 0;
    }

    do {
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    if (ch == '+' || ch == '-') {
        return 0;
    }

    errno = 0;
    parsed = 0;

    while (ch != EOF && isdigit((unsigned char)ch)) {
        unsigned int digit = (unsigned int)(ch - '0');

        digit_seen = 1;

        if (parsed > (UINT64_MAX - digit) / UINTMAX_C(10)) {
            errno = ERANGE;
        } else if (errno != ERANGE) {
            parsed = parsed * UINTMAX_C(10) + digit;
        }

        ch = getchar();
    }

    if (!digit_seen || errno == ERANGE) {
        while (ch != '\n' && ch != EOF) {
            ch = getchar();
        }
        return 0;
    }

    while (ch != '\n' && ch != EOF) {
        if (!isspace((unsigned char)ch)) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);
            return 0;
        }
        ch = getchar();
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

    if (!sum_odd_squares(value, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}