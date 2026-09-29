#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int64_t x1;
    int64_t y1;
    int64_t gcd = extended_gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

static int solve_diophantine(int64_t a, int64_t b, int64_t n,
                             int64_t *x, int64_t *y)
{
    if (x == NULL || y == NULL || (a == 0 && b == 0)) {
        return 0;
    }

    int64_t x0;
    int64_t y0;
    int64_t gcd = extended_gcd(a, b, &x0, &y0);

    if (gcd == 0 || n % gcd != 0) {
        return 0;
    }

    int64_t factor = n / gcd;
    *x = x0 * factor;
    *y = y0 * factor;
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
        puts("No integer solution");
        return 0;
    }

    printf("x = %" PRId64 ", y = %" PRId64 "\n", x, y);
    return 0;
}