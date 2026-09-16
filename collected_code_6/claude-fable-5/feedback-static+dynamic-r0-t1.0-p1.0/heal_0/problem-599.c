#include <stdio.h>
#include <stdlib.h>

int sum_and_average(unsigned int n, unsigned long long *sum, double *average)
{
    if (sum == NULL || average == NULL) {
        return -1;
    }
    if (n == 0U || n > 1000000000U) {
        return -1;
    }
    *sum = ((unsigned long long)n * ((unsigned long long)n + 1ULL)) / 2ULL;
    *average = (double)*sum / (double)n;
    return 0;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned long long sum = 0ULL;
    double average = 0.0;

    printf("Enter a positive integer n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (sum_and_average(n, &sum, &average) != 0) {
        fprintf(stderr, "Error: n must be between 1 and 1000000000.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of first %u natural numbers: %llu\n", n, sum);
    printf("Average of first %u natural numbers: %.2f\n", n, average);

    return EXIT_SUCCESS;
}