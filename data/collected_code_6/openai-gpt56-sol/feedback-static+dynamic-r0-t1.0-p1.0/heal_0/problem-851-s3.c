#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_inverse_divisors(unsigned long long n, long double *result)
{
    unsigned long long i;
    long double sum = 0.0L;

    if (n == 0 || result == NULL) {
        return -1;
    }

    for (i = 1; i <= n / i; ++i) {
        if (n % i == 0) {
            unsigned long long paired_divisor = n / i;

            sum += 1.0L / (long double)i;
            if (paired_divisor != i) {
                sum += 1.0L / (long double)paired_divisor;
            }
        }
    }

    *result = sum;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long n;
    long double result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || n == 0 || argv[1][0] == '-') {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    if (sum_of_inverse_divisors(n, &result) != 0 || !isfinite(result)) {
        fprintf(stderr, "Unable to calculate the result\n");
        return EXIT_FAILURE;
    }

    if (printf("%.18Lg\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}