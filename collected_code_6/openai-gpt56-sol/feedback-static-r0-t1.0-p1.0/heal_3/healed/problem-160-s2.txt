#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;

static uint64_t magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
}

static uint64_t gcd_extended(uint64_t a, uint64_t b,
                             int128_t *x, int128_t *y)
{
    int128_t old_r = (int128_t)a;
    int128_t r = (int128_t)b;
    int128_t old_s = 1;
    int128_t s = 0;
    int128_t old_t = 0;
    int128_t t = 1;

    while (r != 0) {
        int128_t quotient = old_r / r;
        int128_t next_r = old_r - quotient * r;
        int128_t next_s = old_s - quotient * s;
        int128_t next_t = old_t - quotient * t;

        old_r = r;
        r = next_r;
        old_s = s;
        s = next_s;
        old_t = t;
        t = next_t;
    }

    *x = old_s;
    *y = old_t;
    return (uint64_t)old_r;
}

static int solve_diophantine(int64_t a, int64_t b, int64_t n,
                             int128_t *x, int128_t *y)
{
    uint64_t divisor;
    int128_t base_x;
    int128_t base_y;
    int128_t factor;

    if (x == NULL || y == NULL) {
        return 0;
    }

    if (a == 0 && b == 0) {
        if (n != 0) {
            return 0;
        }

        *x = 0;
        *y = 0;
        return 1;
    }

    divisor = gcd_extended(magnitude(a), magnitude(b), &base_x, &base_y);

    if ((int128_t)n % (int128_t)divisor != 0) {
        return 0;
    }

    factor = (int128_t)n / (int128_t)divisor;
    *x = base_x * factor * (a < 0 ? -1 : 1);
    *y = base_y * factor * (b < 0 ? -1 : 1);

    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int print_int128(int128_t value)
{
    uint128_t remaining;
    char digits[40];
    size_t length = 0;
    int negative = value < 0;

    if (negative) {
        remaining = (uint128_t)(-(value + 1)) + 1;
    } else {
        remaining = (uint128_t)value;
    }

    do {
        if (length >= sizeof digits) {
            return 0;
        }

        digits[length++] = (char)('0' + (unsigned int)(remaining % 10));
        remaining /= 10;
    } while (remaining != 0);

    if (negative && fputc('-', stdout) == EOF) {
        return 0;
    }

    while (length > 0) {
        if (fputc((unsigned char)digits[--length], stdout) == EOF) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    int64_t a;
    int64_t b;
    int64_t n;
    int128_t x;
    int128_t y;

    if (argc != 4) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s a b n\n", program);
        return EXIT_FAILURE;
    }

    if (!parse_int64(argv[1], &a) ||
        !parse_int64(argv[2], &b) ||
        !parse_int64(argv[3], &n)) {
        fputs("Invalid integer input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!solve_diophantine(a, b, n, &x, &y)) {
        if (puts("No solution") == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    if (fputs("x = ", stdout) == EOF ||
        !print_int128(x) ||
        fputs(", y = ", stdout) == EOF ||
        !print_int128(y) ||
        fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}