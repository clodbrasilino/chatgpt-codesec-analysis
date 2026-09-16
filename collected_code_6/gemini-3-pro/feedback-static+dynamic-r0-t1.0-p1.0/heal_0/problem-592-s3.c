#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coeff(unsigned int n, unsigned int k);
unsigned long long sum_of_product_of_binomial_coeffs(unsigned int n);

unsigned long long binomial_coeff(unsigned int n, unsigned int k) {
    if (k > n) {
        return 0;
    }
    if (k > n - k) {
        k = n - k;
    }
    
    unsigned long long res = 1;
    for (unsigned int i = 0; i < k; ++i) {
        res = res * (n - i);
        res = res / (i + 1);
    }
    
    return res;
}

unsigned long long sum_of_product_of_binomial_coeffs(unsigned int n) {
    return binomial_coeff(2 * n, n);
}

int main(void) {
    unsigned int n = 0;
    
    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n > 33) {
        return EXIT_FAILURE;
    }
    
    unsigned long long result = sum_of_product_of_binomial_coeffs(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}