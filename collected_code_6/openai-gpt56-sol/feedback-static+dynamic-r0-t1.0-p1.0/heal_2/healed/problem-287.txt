#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_squares(uint64_t n, uint64_t *result)
{
    const uint64_t max_n = UINT64_C(2097151);
    uint64_t a;
    uint64_t b;
    uint64_t c;

    if (result == NULL || n > max_n) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);
    c = UINT64_C(2) * n + UINT64_C(1);

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    if (a % UINT64_C(2) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    *result = UINT64_C(4) * a * b * c;
    return 1;
}

int main(void)
{
    uintmax_t value;
    uint64_t result;
    int ch;

    if (scanf("%" SCNuMAX, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\r' ||
             ch == '\n' || ch == '\f' || ch == '\v');

    if (ch != EOF || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;

    if (!sum_even_squares((uint64_t)value, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}