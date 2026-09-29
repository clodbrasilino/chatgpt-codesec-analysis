#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int checked_subtract(int64_t a, int64_t b, int64_t *result)
{
    return result != NULL && !__builtin_sub_overflow(a, b, result);
}

static int checked_multiply(int64_t a, int64_t b, int64_t *result)
{
    return result != NULL && !__builtin_mul_overflow(a, b, result);
}

static int extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y,
                        int64_t *gcd)
{
    int64_t old_r = a;
    int64_t r = b;
    int64_t old_s = 1;
    int64_t s = 0;
    int64_t old_t = 0;
    int64_t t = 1;

    if (x == NULL || y == NULL || gcd == NULL) {
        return 0;
    }

    while (r != 0) {
        int64_t quotient;
        int64_t remainder;
        int64_t product;
        int64_t next_s;
        int64_t next_t;

        if (old_r == INT64_MIN && r == -1) {
            return 0;
        }

        quotient = old_r / r;
        remainder = old_r % r;

        if (!checked_multiply(quotient, s, &product) ||
            !checked_subtract(old_s, product, &next_s) ||
            !checked_multiply(quotient, t, &product) ||
            !checked_subtract(old_t, product, &next_t)) {
            return 0;
        }

        old_r = r;
        r = remainder;
        old_s = s;
        s = next_s;
        old_t = t;
        t = next_t;
    }

    if (old_r < 0) {
        if (old_r == INT64_MIN || old_s == INT64_MIN ||
            old_t == INT64_MIN) {
            return 0;
        }

        old_r = -old_r;
        old_s = -old_s;
        old_t = -old_t;
    }

    *x = old_s;
    *y = old_t;
    *gcd = old_r;
    return 1;
}

static int solve_diophantine(int64_t a, int64_t b, int64_t n,
                             int64_t *x, int64_t *y)
{
    int64_t x0;
    int64_t y0;
    int64_t gcd;
    int64_t factor;
    int64_t result_x;
    int64_t result_y;

    if (x == NULL || y == NULL || (a == 0 && b == 0)) {
        return 0;
    }

    if (!extended_gcd(a, b, &x0, &y0, &gcd) || gcd == 0) {
        return 0;
    }

    if (n % gcd != 0) {
        return 0;
    }

    factor = n / gcd;

    if (!checked_multiply(x0, factor, &result_x) ||
        !checked_multiply(y0, factor, &result_y)) {
        return 0;
    }

    *x = result_x;
    *y = result_y;
    return 1;
}

static int is_space_character(char c)
{
    return c == ' ' || c == '\t' || c == '\r' ||
           c == '\n' || c == '\v' || c == '\f';
}

static int parse_int64(const char **cursor, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    while (is_space_character(**cursor)) {
        ++*cursor;
    }

    if (**cursor == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    *cursor = end;
    return 1;
}

static int read_input(int64_t *a, int64_t *b, int64_t *n)
{
    enum { INPUT_BUFFER_SIZE = 256 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];
    const char *cursor;

    if (a == NULL || b == NULL || n == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (ferror(stdin)) {
        return 0;
    }

    cursor = buffer;

    if (!parse_int64(&cursor, a) ||
        !parse_int64(&cursor, b) ||
        !parse_int64(&cursor, n)) {
        return 0;
    }

    while (is_space_character(*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return 0;
    }

    return 1;
}

int main(void)
{
    int64_t a;
    int64_t b;
    int64_t n;
    int64_t x;
    int64_t y;

    if (!read_input(&a, &b, &n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!solve_diophantine(a, b, n, &x, &y)) {
        puts("No representable integer solution");
        return EXIT_SUCCESS;
    }

    printf("x = %" PRId64 ", y = %" PRId64 "\n", x, y);
    return EXIT_SUCCESS;
}