#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n || n < 0) {
        return 0;
    }
    
    if (k == 0 || k == n) {
        return 1;
    }
    
    if (k > n - k) {
        k = n - k;
    }
    
    long long result = 1;
    for (int i = 0; i < k; i++) {
        long long numerator = n - i;
        long long denominator = i + 1;
        
        if (result > LLONG_MAX / numerator) {
            return -1;
        }
        
        result = result * numerator / denominator;
    }
    
    return result;
}

int main(void) {
    int n, k;
    
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0 || k < 0) {
        fprintf(stderr, "Error: n and k must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = binomial_coefficient(n, k);
    
    if (result == -1 && n > 0 && k > 0 && k < n) {
        fprintf(stderr, "Error: Result exceeds maximum representable value\n");
        return EXIT_FAILURE;
    }
    
    printf("C(%d, %d) = %lld\n", n, k, result);
    
    return EXIT_SUCCESS;
}