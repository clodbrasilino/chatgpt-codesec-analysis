#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n / 2) {
        k = n - k;
    }
    
    unsigned long long res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - i + 1);
        res = res / i;
    }
    return res;
}

unsigned long long sum_even_index_binomial_coefficients(int n) {
    if (n < 0 || n >= 64) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    return 1ULL << (n - 1);
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n < 0 || n >= 64) {
        return 1;
    }
    
    unsigned long long sum = sum_even_index_binomial_coefficients(n);
    printf("%llu\n", sum);
    
    return 0;
}