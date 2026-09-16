#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int calculate_sum_and_average(unsigned long long n,
                                     unsigned long long *sum,
                                     long double *average)
{
    if (sum == NULL || average == NULL || n == 0 ||
        (n == ULLONG_MAX && n % 2 != 0)) {
        return -1;
    }

    if (n % 2 == 0) {
        if (n / 2 > ULLONG_MAX / (n + 1)) {
            return -1;
        }
        *sum = (n / 2) * (n + 1);
    } else {
        if (n > ULLONG_MAX / ((n + 1) / 2)) {
            return -1;
        }
        *sum = n * ((n + 1) / 2);
    }

    *average = (long double)(n + 1) / 2.0L;
    return 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    unsigned long long n;
    unsigned long long sum;
    long double average;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0' || n == 0) {
        fputs("Input must be a positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_sum_and_average(n, &sum, &average) != 0) {
        fputs("The result is outside the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Sum: %llu\n", sum);
    printf("Average: %.2Lf\n", average);

    return EXIT_SUCCESS;
}