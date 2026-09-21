#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

unsigned long long lobb_number(int n, int m) {
    if (n < 0 || m < 0 || n < m) {
        return 0;
    }
    
    unsigned long long bin_coeff = binomial_coefficient(2 * n, n + m);
    unsigned long long lobb = ((2ULL * m + 1ULL) * bin_coeff) / (n + m + 1ULL);
    
    return lobb;
}

int main(int argc, const char *const argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    
    long n_val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || n_val < 0 || n_val > INT_MAX) {
        fprintf(stderr, "Invalid input for n.\n");
        return 1;
    }
    int n = (int)n_val;
    
    long m_val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || m_val < 0 || m_val > INT_MAX) {
        fprintf(stderr, "Invalid input for m.\n");
        return 1;
    }
    int m = (int)m_val;
    
    if (n < m) {
        fprintf(stderr, "Invalid input bounds. Ensure n >= m >= 0.\n");
        return 1;
    }
    
    unsigned long long result = lobb_number(n, m);
    printf("%llu\n", result);
    
    return 0;
}