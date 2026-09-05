#include <stdio.h>
#include <stdlib.h>

long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) {
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
        result = result * (n - i) / (i + 1);
    }
    return result;
}

long long sum_of_product_of_binomials(int n) {
    long long sum = 0;
    for (int i = 0; i <= n; i++) {
        long long coeff = binomial_coefficient(n, i);
        sum += coeff * coeff;
    }
    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_of_product_of_binomials(n);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}