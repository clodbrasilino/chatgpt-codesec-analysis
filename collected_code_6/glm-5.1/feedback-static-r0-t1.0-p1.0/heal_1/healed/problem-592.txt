#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long binomial_coefficient(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n - k) {
        k = n - k;
    }
    long long res = 1;
    for (int i = 1; i <= k; i++) {
        if (res > LLONG_MAX / (n - k + i)) {
            return -1;
        }
        res *= (n - k + i);
        if (res / i != res / i) {
            return -1;
        }
        res /= i;
    }
    return res;
}

long long sum_of_product_binomial(int n) {
    if (n < 0) {
        return -1;
    }
    long long sum = 0;
    for (int k = 0; k <= n; k++) {
        long long c_nk = binomial_coefficient(n, k);
        if (c_nk < 0) {
            return -1;
        }
        long long c_nk_1 = binomial_coefficient(n, k + 1);
        if (c_nk_1 < 0) {
            return -1;
        }
        long long product = c_nk * c_nk_1;
        if (c_nk != 0 && product / c_nk != c_nk_1) {
            return -1;
        }
        if (sum > LLONG_MAX - product) {
            return -1;
        }
        sum += product;
    }
    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 1000) {
        fprintf(stderr, "Invalid input. n must be a non-negative integer <= 1000.\n");
        return 1;
    }
    long long result = sum_of_product_binomial((int)val);
    if (result < 0) {
        fprintf(stderr, "Overflow or error occurred during calculation.\n");
        return 1;
    }
    printf("%lld\n", result);
    return 0;
}