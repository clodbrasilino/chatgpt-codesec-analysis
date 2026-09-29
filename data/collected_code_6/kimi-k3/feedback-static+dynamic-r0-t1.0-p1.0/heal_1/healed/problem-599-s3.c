#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int sum_and_average(int n, long long *sum, double *average)
{
    if (n < 1 || sum == NULL || average == NULL) {
        return -1;
    }

    if ((long long)n > (LLONG_MAX / (long long)(n + 1)) / 2) {
        return -1;
    }

    *sum = (long long)n * (long long)(n + 1) / 2LL;
    *average = (double)*sum / (double)n;
    
    return 0;
}

int main(void)
{
    int n;
    long long sum;
    double average;
    char buffer[256];
    char *endptr;
    long val;

    printf("Enter a positive integer: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || *endptr != '\n' || val < 1 || val > INT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    n = (int)val;

    if (sum_and_average(n, &sum, &average) != 0) {
        fprintf(stderr, "Calculation failed\n");
        return EXIT_FAILURE;
    }

    printf("Sum of first %d natural numbers: %lld\n", n, sum);
    printf("Average: %.2f\n", average);

    return EXIT_SUCCESS;
}