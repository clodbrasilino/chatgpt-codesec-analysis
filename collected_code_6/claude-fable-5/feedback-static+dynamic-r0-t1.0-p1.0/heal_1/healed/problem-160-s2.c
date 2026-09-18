#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int checked_mul(long long a, long long b, long long *res)
{
    if (a == 0 || b == 0) {
        *res = 0;
        return 0;
    }
    if (a > 0) {
        if (b > 0) {
            if (a > LLONG_MAX / b) {
                return -1;
            }
        } else {
            if (b < LLONG_MIN / a) {
                return -1;
            }
        }
    } else {
        if (b > 0) {
            if (a < LLONG_MIN / b) {
                return -1;
            }
        } else {
            if (a < LLONG_MAX / b) {
                return -1;
            }
        }
    }
    *res = a * b;
    return 0;
}

static int checked_add(long long a, long long b, long long *res)
{
    if (b > 0 && a > LLONG_MAX - b) {
        return -1;
    }
    if (b < 0 && a < LLONG_MIN - b) {
        return -1;
    }
    *res = a + b;
    return 0;
}

static int checked_neg(long long a, long long *res)
{
    if (a == LLONG_MIN) {
        return -1;
    }
    *res = -a;
    return 0;
}

static long long extended_gcd(long long a, long long b, long long *x, long long *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1;
    long long y1;
    long long g = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

static int solve_equation(long long a, long long b, long long n, long long *x, long long *y)
{
    if (x == NULL || y == NULL) {
        return -1;
    }
    if (a == LLONG_MIN || b == LLONG_MIN) {
        return -1;
    }
    if (a == 0 && b == 0) {
        if (n == 0) {
            *x = 0;
            *y = 0;
            return 0;
        }
        return -1;
    }
    long long x0;
    long long y0;
    long long abs_a = (a < 0) ? -a : a;
    long long abs_b = (b < 0) ? -b : b;
    long long g = extended_gcd(abs_a, abs_b, &x0, &y0);
    if (g == 0 || n % g != 0) {
        return -1;
    }
    long long factor = n / g;
    long long xs;
    long long ys;
    if (checked_mul(x0, factor, &xs) != 0) {
        return -1;
    }
    if (checked_mul(y0, factor, &ys) != 0) {
        return -1;
    }
    if (a < 0) {
        if (checked_neg(xs, &xs) != 0) {
            return -1;
        }
    }
    if (b < 0) {
        if (checked_neg(ys, &ys) != 0) {
            return -1;
        }
    }
    *x = xs;
    *y = ys;
    return 0;
}

int main(void)
{
    long long a;
    long long b;
    long long n;
    long long x;
    long long y;

    printf("Enter a, b, n: ");
    if (scanf("%lld %lld %lld", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (solve_equation(a, b, n, &x, &y) != 0) {
        printf("No integer solution exists for %lldx + %lldy = %lld\n", a, b, n);
        return EXIT_FAILURE;
    }

    printf("Solution: x = %lld, y = %lld\n", x, y);

    long long ax;
    long long by;
    long long sum;
    if (checked_mul(a, x, &ax) == 0 &&
        checked_mul(b, y, &by) == 0 &&
        checked_add(ax, by, &sum) == 0) {
        printf("Check: %lld * %lld + %lld * %lld = %lld\n", a, x, b, y, sum);
    } else {
        printf("Check skipped: intermediate values exceed representable range\n");
    }

    return EXIT_SUCCESS;
}