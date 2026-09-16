#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_squares_binomial(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    
    unsigned long long *row = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (row == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    row[0] = 1;
    for (int i = 0; i < n; i++) {
        row[i + 1] = row[i] * (n - i) / (i + 1);
    }
    
    unsigned long long sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += row[i] * row[i];
    }
    
    free(row);
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = sum_of_squares_binomial(n);
    printf("Sum of squares of binomial coefficients for n = %d: %llu\n", n, result);
    
    return EXIT_SUCCESS;
}