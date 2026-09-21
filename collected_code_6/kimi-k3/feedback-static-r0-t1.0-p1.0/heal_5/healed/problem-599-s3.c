#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

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
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t len;
    char *endptr;
    long val;

    printf("Enter a positive integer: ");
    
    len = getline(&buffer, &buffer_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || *endptr != '\0' || val < 1 || val > INT_MAX) {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    n = (int)val;

    if (sum_and_average(n, &sum, &average) != 0) {
        fprintf(stderr, "Calculation failed\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Sum of first %d natural numbers: %lld\n", n, sum);
    printf("Average: %.2f\n", average);

    free(buffer);
    return EXIT_SUCCESS;
}