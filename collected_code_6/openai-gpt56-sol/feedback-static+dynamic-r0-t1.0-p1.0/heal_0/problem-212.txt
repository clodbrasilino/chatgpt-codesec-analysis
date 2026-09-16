#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    const uint64_t max_n = UINT64_C(71581);
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
    uint64_t e;

    if (result == NULL || n > max_n) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);
    c = (UINT64_C(2) * n) + UINT64_C(1);
    d = (n * n) + n - UINT64_C(1);
    e = UINT64_C(30);

    if (a % UINT64_C(2) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }
    e /= UINT64_C(2);

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }
    e /= UINT64_C(3);

    if (a % UINT64_C(5) == 0) {
        a /= UINT64_C(5);
    } else if (b % UINT64_C(5) == 0) {
        b /= UINT64_C(5);
    } else if (c % UINT64_C(5) == 0) {
        c /= UINT64_C(5);
    } else {
        d /= UINT64_C(5);
    }
    e /= UINT64_C(5);

    if (e != UINT64_C(1)) {
        return 0;
    }

    *result = a * b * c * d;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!sum_fourth_powers(n, &sum)) {
        fputs("Result exceeds uint64_t range\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}