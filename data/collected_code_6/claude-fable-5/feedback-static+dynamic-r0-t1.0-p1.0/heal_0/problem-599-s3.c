#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_and_average(unsigned int n, unsigned long long *sum, double *average)
{
    if (sum == NULL || average == NULL) {
        return -1;
    }

    if (n == 0U) {
        return -1;
    }

    if (n > 4294967294U) {
        return -1;
    }

    unsigned long long un = (unsigned long long)n;
    *sum = (un * (un + 1ULL)) / 2ULL;
    *average = (double)*sum / (double)n;

    return 0;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned long long sum = 0ULL;
    double average = 0.0;

    printf("Enter n: ");

    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (sum_and_average(n, &sum, &average) != 0) {
        fprintf(stderr, "Error: n must be a positive natural number within range\n");
        return EXIT_FAILURE;
    }

    printf("Sum of first %u natural numbers: %llu\n", n, sum);
    printf("Average of first %u natural numbers: %.2f\n", n, average);

    return EXIT_SUCCESS;
}