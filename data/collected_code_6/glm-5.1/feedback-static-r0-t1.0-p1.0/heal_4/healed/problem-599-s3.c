#include <stdio.h>
#include <stdlib.h>

void calculate_sum_average(int n, long long *sum, double *average) {
    if (n <= 0 || sum == NULL || average == NULL) {
        if (sum != NULL) *sum = 0;
        if (average != NULL) *average = 0.0;
        return;
    }
    *sum = (long long)n * (n + 1) / 2;
    *average = (double)(*sum) / n;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    long long val;
    char *endptr;
    val = strtoll(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || val <= 0 || val > 2147483647) {
        fprintf(stderr, "Error: n must be a positive integer within valid range.\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    long long sum;
    double average;
    
    calculate_sum_average(n, &sum, &average);
    
    printf("Sum of first %d natural numbers: %lld\n", n, sum);
    printf("Average of first %d natural numbers: %.2f\n", n, average);
    
    return EXIT_SUCCESS;
}