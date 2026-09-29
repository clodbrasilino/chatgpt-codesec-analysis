#include <stdio.h>
#include <stdlib.h>

void sum_and_average(int n, long long *sum, double *average) {
    if (sum == NULL || average == NULL) {
        fprintf(stderr, "Invalid input pointers\n");
        exit(EXIT_FAILURE);
    }
    
    *sum = (long long)n * (n + 1) / 2;
    *average = (double)(*sum) / n;
}

int main(void) {
    int n;
    long long sum;
    double average;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }
    
    sum_and_average(n, &sum, &average);
    
    printf("Sum: %lld\n", sum);
    printf("Average: %.2f\n", average);
    
    return EXIT_SUCCESS;
}