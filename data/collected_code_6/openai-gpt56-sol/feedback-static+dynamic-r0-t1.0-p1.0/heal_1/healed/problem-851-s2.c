#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_inverse_divisors(unsigned long long n, long double *result)
{
    unsigned long long divisor;
    long double sum = 0.0L;

    if (n == 0 || result == NULL) {
        return -1;
    }

    for (divisor = 1; divisor <= n / divisor; ++divisor) {
        if (n % divisor == 0) {
            const unsigned long long paired_divisor = n / divisor;

            sum += 1.0L / (long double)divisor;
            if (paired_divisor != divisor) {
                sum += 1.0L / (long double)paired_divisor;
            }
        }
    }

    if (!isfinite(sum)) {
        return -1;
    }

    *result = sum;
    return 0;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    unsigned long long n;
    long double result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || n == 0) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    if (sum_inverse_divisors(n, &result) != 0) {
        fprintf(stderr, "Failed to calculate the sum\n");
        return EXIT_FAILURE;
    }

    if (printf("%.18Lg\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}