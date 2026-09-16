#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int count_squares(unsigned long long width,
                         unsigned long long height,
                         unsigned long long *result)
{
    unsigned long long n = width < height ? width : height;
    unsigned long long m = width > height ? width : height;
    unsigned long long a;
    unsigned long long b;

    if (result == NULL) {
        return 0;
    }

    if (n == ULLONG_MAX) {
        return 0;
    }

    a = n;
    b = n + 1ULL;

    if ((a & 1ULL) == 0ULL) {
        a /= 2ULL;
    } else {
        b /= 2ULL;
    }

    if (a != 0ULL && b > ULLONG_MAX / a) {
        return 0;
    }

    a *= b;

    if (m == ULLONG_MAX) {
        return 0;
    }

    b = m + 1ULL - n;

    if (a != 0ULL && b > ULLONG_MAX / a) {
        return 0;
    }

    *result = a * b;

    if (n > 1ULL) {
        unsigned long long c = n - 1ULL;
        unsigned long long d = n;
        unsigned long long e = n + 1ULL;

        if ((c & 1ULL) == 0ULL) {
            c /= 2ULL;
        } else if ((d & 1ULL) == 0ULL) {
            d /= 2ULL;
        } else {
            e /= 2ULL;
        }

        if (c % 3ULL == 0ULL) {
            c /= 3ULL;
        } else if (d % 3ULL == 0ULL) {
            d /= 3ULL;
        } else {
            e /= 3ULL;
        }

        if (c != 0ULL && d > ULLONG_MAX / c) {
            return 0;
        }

        c *= d;

        if (c != 0ULL && e > ULLONG_MAX / c) {
            return 0;
        }

        c *= e;

        if (*result < c) {
            return 0;
        }

        *result -= c;
    }

    return 1;
}

int main(void)
{
    unsigned long long width;
    unsigned long long height;
    unsigned long long result;

    if (scanf("%llu %llu", &width, &height) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_squares(width, height, &result)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}