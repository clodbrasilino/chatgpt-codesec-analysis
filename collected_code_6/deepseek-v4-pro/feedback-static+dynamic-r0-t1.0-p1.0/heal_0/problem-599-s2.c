#include <stdio.h>
#include <stdlib.h>

void calculate_sum_and_average(int n, long *sum, double *average) {
    if (n <= 0) {
        *sum = 0;
        *average = 0.0;
        return;
    }
    
    *sum = (long)n * (n + 1) / 2;
    *average = (double)*sum / n;
}

int main(void) {
    int n;
    long sum;
    double average;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "Please enter a positive integer\n");
        return EXIT_FAILURE;
    }
    
    calculate_sum_and_average(n, &sum, &average);
    
    printf("Sum of first %d natural numbers: %ld\n", n, sum);
    printf("Average of first %d natural numbers: %.2f\n", n, average);
    
    return EXIT_SUCCESS;
}