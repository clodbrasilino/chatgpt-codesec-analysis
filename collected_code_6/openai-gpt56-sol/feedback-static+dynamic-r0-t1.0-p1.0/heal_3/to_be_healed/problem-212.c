#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    const uint64_t max_n = UINT64_C(71581);
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;

    if (result == NULL || n > max_n) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);
    c = UINT64_C(2) * n + UINT64_C(1);
    d = n * n + n - UINT64_C(1);

    if (a % UINT64_C(2) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    if (a % UINT64_C(5) == 0) {
        a /= UINT64_C(5);
    } else if (b % UINT64_C(5) == 0) {
        b /= UINT64_C(5);
    } else if (c % UINT64_C(5) == 0) {
        c /= UINT64_C(5);
    } else {
        d /= UINT64_C(5);
    }

    *result = a * b * c * d;
    return 1;
}

int main(void)
{
    unsigned long long value;
    uint64_t n;
    uint64_t sum;
    int ch;

    errno = 0;

    if (scanf("%llu", &value) != 1 || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' ||
             ch == '\v' || ch == '\f');

    if (ch != EOF || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (uint64_t)value;

    if (!sum_fourth_powers(n, &sum)) {
        fputs("Result exceeds uint64_t range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}