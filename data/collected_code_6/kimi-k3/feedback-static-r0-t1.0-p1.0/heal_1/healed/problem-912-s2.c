#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static unsigned long long lobb_number(int n, int m)
{
    if (n < 0 || m < 0 || m > n) {
        return 0ULL;
    }

    if (m > n - m) {
        m = n - m;
    }

    unsigned long long result = 1ULL;

    for (int i = 0; i < m; ++i) {
        int numerator = n - i;
        int denominator = i + 1;

        if (numerator % denominator == 0) {
            int factor = numerator / denominator;

            if (factor != 0 && result > ULLONG_MAX / (unsigned long long)factor) {
                errno = ERANGE;
                return 0ULL;
            }

            result *= (unsigned long long)factor;
        } else if (result % (unsigned long long)denominator == 0ULL) {
            result /= (unsigned long long)denominator;

            if (numerator != 0 && result > ULLONG_MAX / (unsigned long long)numerator) {
                errno = ERANGE;
                return 0ULL;
            }

            result *= (unsigned long long)numerator;
        } else {
            if (numerator != 0 && result > ULLONG_MAX / (unsigned long long)numerator) {
                errno = ERANGE;
                return 0ULL;
            }

            result *= (unsigned long long)numerator;
            result /= (unsigned long long)denominator;
        }
    }

    if (result % (unsigned long long)(2 * n - m + 1) != 0ULL) {
        return 0ULL;
    }

    result /= (unsigned long long)(2 * n - m + 1);

    return result;
}

int main(void)
{
    int n;
    int m;

    printf("Enter n and m: ");

    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    unsigned long long result = lobb_number(n, m);

    if (errno != 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("L(%d, %d) = %llu\n", n, m, result);

    return EXIT_SUCCESS;
}