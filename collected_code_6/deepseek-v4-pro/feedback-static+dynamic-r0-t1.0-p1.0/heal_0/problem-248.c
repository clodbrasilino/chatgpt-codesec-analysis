#include <stdio.h>
#include <stdlib.h>

double harmonic_sum(int n) {
    if (n < 1) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 1; i <= n - 1; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter a positive integer n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 1) {
        fprintf(stderr, "n must be positive\n");
        return EXIT_FAILURE;
    }
    
    double result = harmonic_sum(n);
    printf("Harmonic sum of %d-1 terms: %.10f\n", n, result);
    
    return EXIT_SUCCESS;
}