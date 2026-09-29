#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int checked_add(int64_t a, int64_t b, int64_t *result)
{
    return !__builtin_add_overflow(a, b, result);
}

static int checked_subtract(int64_t a, int64_t b, int64_t *result)
{
    return !__builtin_sub_overflow(a, b, result);
}

static int checked_multiply(int64_t a, int64_t b, int64_t *result)
{
    return !__builtin_mul_overflow(a, b, result);
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
            !checked_subtract(old_s, product, &next_s)) {
            return 0;
        }

        if (!checked_multiply(quotient, t, &product) ||
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

int main(void)
{
    int64_t a;
    int64_t b;
    int64_t n;
    int64_t x;
    int64_t y;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64, &a, &b, &n) != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');

    if (ch != EOF) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!solve_diophantine(a, b, n, &x, &y)) {
        puts("No representable integer solution");
        return 0;
    }

    printf("x = %" PRId64 ", y = %" PRId64 "\n", x, y);
    return 0;
}