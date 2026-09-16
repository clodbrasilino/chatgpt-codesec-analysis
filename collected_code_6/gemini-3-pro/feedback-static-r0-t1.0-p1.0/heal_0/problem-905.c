#include <stdio.h>
#include <stdlib.h>

unsigned long long calculateFactorial(int n) {
    if (n < 0) {
        return 0; 
    }
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

unsigned long long calculateBinomialCoefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    
    unsigned long long num = 1;
    unsigned long long den = 1;
    
    if (k > n - k) {
        k = n - k;
    }
    
    for (int i = 0; i < k; ++i) {
        num *= (n - i);
        den *= (i + 1);
    }
    
    return num / den;
}

unsigned long long sumOfSquaresOfBinomialCoefficients(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long result = calculateBinomialCoefficient(2 * n, n);
    return result;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0 || n > 33) {
        fprintf(stderr, "Input out of range. Please provide a non-negative integer up to 33 to prevent overflow.\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long sum = sumOfSquaresOfBinomialCoefficients(n);
    printf("%llu\n", sum);
    
    return EXIT_SUCCESS;
}