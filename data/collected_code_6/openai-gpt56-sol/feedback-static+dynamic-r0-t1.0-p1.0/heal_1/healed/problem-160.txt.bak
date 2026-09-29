#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int checked_add(int64_t a, int64_t b, int64_t *result)
{
#if defined(__GNUC__) || defined(__clang__)
    return !__builtin_add_overflow(a, b, result);
#else
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }
    *result = a + b;
    return 1;
#endif
}

static int checked_sub(int64_t a, int64_t b, int64_t *result)
{
#if defined(__GNUC__) || defined(__clang__)
    return !__builtin_sub_overflow(a, b, result);
#else
    if ((b > 0 && a < INT64_MIN + b) ||
        (b < 0 && a > INT64_MAX + b)) {
        return 0;
    }
    *result = a - b;
    return 1;
#endif
}

static int checked_mul(int64_t a, int64_t b, int64_t *result)
{
#if defined(__GNUC__) || defined(__clang__)
    return !__builtin_mul_overflow(a, b, result);
#else
    if (a == 0 || b == 0) {
        *result = 0;
        return 1;
    }

    if ((a == -1 && b == INT64_MIN) ||
        (b == -1 && a == INT64_MIN)) {
        return 0;
    }

    if (a > 0) {
        if (b > 0) {
            if (a > INT64_MAX / b) {
                return 0;
            }
        } else if (b < INT64_MIN / a) {
            return 0;
        }
    } else {
        if (b > 0) {
            if (a < INT64_MIN / b) {
                return 0;
            }
        } else if (a < INT64_MAX / b) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
#endif
}

static int solve_diophantine(int64_t a, int64_t b, int64_t n,
                             int64_t *x, int64_t *y)
{
    if (x == NULL || y == NULL || (a == 0 && b == 0)) {
        return 0;
    }

    int64_t old_r = a;
    int64_t r = b;
    int64_t old_s = 1;
    int64_t s = 0;
    int64_t old_t = 0;
    int64_t t = 1;

    while (r != 0) {
        if (old_r == INT64_MIN && r == -1) {
            return 0;
        }

        int64_t q = old_r / r;
        int64_t next_r = old_r % r;
        int64_t product;
        int64_t next_s;
        int64_t next_t;

        if (!checked_mul(q, s, &product) ||
            !checked_sub(old_s, product, &next_s)) {
            return 0;
        }

        if (!checked_mul(q, t, &product) ||
            !checked_sub(old_t, product, &next_t)) {
            return 0;
        }

        old_r = r;
        r = next_r;
        old_s = s;
        s = next_s;
        old_t = t;
        t = next_t;
    }

    if (old_r == INT64_MIN) {
        return 0;
    }

    if (old_r < 0) {
        old_r = -old_r;

        if (!checked_sub(0, old_s, &old_s) ||
            !checked_sub(0, old_t, &old_t)) {
            return 0;
        }
    }

    if (old_r == 0 || n % old_r != 0) {
        return 0;
    }

    int64_t factor = n / old_r;
    int64_t result_x;
    int64_t result_y;

    if (!checked_mul(old_s, factor, &result_x) ||
        !checked_mul(old_t, factor, &result_y)) {
        return 0;
    }

    int64_t verification;
    int64_t term;

    if (!checked_mul(a, result_x, &verification) ||
        !checked_mul(b, result_y, &term) ||
        !checked_add(verification, term, &verification) ||
        verification != n) {
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

    if (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64, &a, &b, &n) != 3) {
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