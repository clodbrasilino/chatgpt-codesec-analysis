#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_inverse_divisors(unsigned long long n, long double *sum)
{
    unsigned long long divisor;
    long double result = 0.0L;

    if (n == 0 || sum == NULL) {
        return -1;
    }

    for (divisor = 1; divisor <= n / divisor; ++divisor) {
        if (n % divisor == 0) {
            unsigned long long paired_divisor = n / divisor;

            result += 1.0L / (long double)divisor;
            if (paired_divisor != divisor) {
                result += 1.0L / (long double)paired_divisor;
            }
        }
    }

    *sum = result;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long number;
    long double sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || number == 0) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    if (sum_of_inverse_divisors(number, &sum) != 0 || !isfinite(sum)) {
        fprintf(stderr, "Unable to calculate the result\n");
        return EXIT_FAILURE;
    }

    if (printf("%.18Lg\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}