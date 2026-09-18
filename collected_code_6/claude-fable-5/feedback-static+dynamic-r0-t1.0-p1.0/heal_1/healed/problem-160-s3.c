#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long extended_gcd(long long a, long long b, long long *x, long long *y);
int solve_equation(long long a, long long b, long long n, long long *x, long long *y);

long long extended_gcd(long long a, long long b, long long *x, long long *y)
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

int solve_equation(long long a, long long b, long long n, long long *x, long long *y)
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
    long long g = extended_gcd(a < 0 ? -a : a, b < 0 ? -b : b, &x0, &y0);
    if (g == 0 || (n % g) != 0) {
        return -1;
    }
    long long scale = n / g;
    long long xs;
    long long ys;
    if (__builtin_mul_overflow(x0, scale, &xs)) {
        return -1;
    }
    if (__builtin_mul_overflow(y0, scale, &ys)) {
        return -1;
    }
    if (a < 0) {
        if (xs == LLONG_MIN) {
            return -1;
        }
        xs = -xs;
    }
    if (b < 0) {
        if (ys == LLONG_MIN) {
            return -1;
        }
        ys = -ys;
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
        fprintf(stderr, "No solution exists\n");
        return EXIT_FAILURE;
    }

    printf("x = %lld, y = %lld\n", x, y);

    long long ax;
    long long by;
    long long sum;
    if (__builtin_mul_overflow(a, x, &ax) ||
        __builtin_mul_overflow(b, y, &by) ||
        __builtin_add_overflow(ax, by, &sum)) {
        fprintf(stderr, "Verification skipped: result out of range\n");
        return EXIT_FAILURE;
    }

    printf("Verification: %lld * %lld + %lld * %lld = %lld\n", a, x, b, y, sum);

    return EXIT_SUCCESS;
}