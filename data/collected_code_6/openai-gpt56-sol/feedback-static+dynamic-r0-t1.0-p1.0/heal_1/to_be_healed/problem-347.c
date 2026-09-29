#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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

    if (n != 0U && n + 1U < n) {
        return 0;
    }

    a = n;
    b = n + 1U;

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'ULLONG_MAX'
     *  'ULLONG_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (a != 0U && b > ULLONG_MAX / a) {
        return 0;
    }

    a *= b;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'ULLONG_MAX'
     */
    if (m > ULLONG_MAX - 1U || m + 1U < n) {
        return 0;
    }

    b = m + 1U - n;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'ULLONG_MAX'
     */
    if (a != 0U && b > ULLONG_MAX / a) {
        return 0;
    }

    *result = a * b;

    if (n > 1U) {
        unsigned long long c = n - 1U;
        unsigned long long d = n;
        unsigned long long e = n + 1U;

        if ((c & 1U) == 0U) {
            c /= 2U;
        } else if ((d & 1U) == 0U) {
            d /= 2U;
        } else {
            e /= 2U;
        }

        if ((c % 3U) == 0U) {
            c /= 3U;
        } else if ((d % 3U) == 0U) {
            d /= 3U;
        } else {
            e /= 3U;
        }

        /* Possible weaknesses found:
         *  use of undeclared identifier 'ULLONG_MAX'
         */
        if (c != 0U && d > ULLONG_MAX / c) {
            return 0;
        }

        c *= d;

        /* Possible weaknesses found:
         *  use of undeclared identifier 'ULLONG_MAX'
         */
        if (c != 0U && e > ULLONG_MAX / c) {
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