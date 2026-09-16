#include <stdio.h>
#include <stdlib.h>

long long sum_squares_binomial(int n) {
    long long coefficient = 1;
    long long sum = 0;
    
    if (n < 0) {
        return -1;
    }
    
    for (int k = 0; k <= n; k++) {
        sum += coefficient * coefficient;
        coefficient = coefficient * (n - k) / (k + 1);
    }
    
    return sum;
}

long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n || n < 0) {
        return 0;
    }
    
    if (k > n - k) {
        k = n - k;
    }
    
    long long result = 1;
    
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    
    return result;
}

long long sum_squares_binomial_direct(int n) {
    long long sum = 0;
    
    if (n < 0) {
        return -1;
    }
    
    for (int k = 0; k <= n; k++) {
        long long coeff = binomial_coefficient(n, k);
        sum += coeff * coeff;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_squares_binomial(n);
    printf("Sum of squares of binomial coefficients for n=%d: %lld\n", n, result);
    printf("Verification: %lld\n", sum_squares_binomial_direct(n));
    
    return EXIT_SUCCESS;
}