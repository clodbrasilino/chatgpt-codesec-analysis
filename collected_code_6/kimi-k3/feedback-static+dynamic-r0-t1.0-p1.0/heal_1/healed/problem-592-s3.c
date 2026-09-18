#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
        if (coeff != 0 && (coeff > INT64_MAX / coeff)) {
            return -1;
        }
        long long square = coeff * coeff;
        if (sum > INT64_MAX - square) {
            return -1;
        }
        sum += square;
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
    if (result == -1) {
        fprintf(stderr, "Overflow detected\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}