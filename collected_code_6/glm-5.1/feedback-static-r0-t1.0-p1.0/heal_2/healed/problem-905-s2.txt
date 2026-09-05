#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    unsigned long long res = 1;
    if (k > n - k) {
        k = n - k;
    }
    for (int i = 0; i < k; i++) {
        if (res > (unsigned long long)-1 / (n - i)) {
            return 0;
        }
        res = res * (n - i) / (i + 1);
    }
    return res;
}

unsigned long long sum_of_squares_of_binomial_coefficients(int n) {
    if (n < 0) {
        return 0;
    }
    unsigned long long sum = 0;
    for (int k = 0; k <= n; k++) {
        unsigned long long coeff = binomial_coefficient(n, k);
        if (coeff == 0 && n > 0 && k > 0 && k < n) {
            return 0;
        }
        if (sum > (unsigned long long)-1 - coeff * coeff) {
            return 0;
        }
        sum += coeff * coeff;
    }
    return sum;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return 1;
    }
    int n = atoi(argv[1]);
    if (n < 0) {
        return 1;
    }
    unsigned long long result = sum_of_squares_of_binomial_coefficients(n);
    printf("%llu\n", result);
    return 0;
}