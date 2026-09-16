#include <stdio.h>
#include <stdlib.h>

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
    long long res = 1;
    for (int i = 1; i <= k; i++) {
        if (res > __LLONG_MAX__ / (n - k + i)) {
            return 0;
        }
        res *= (n - k + i);
        res /= i;
    }
    return res;
}

long long sum_of_product_binomial(int n) {
    if (n < 0) {
        return 0;
    }
    long long sum = 0;
    for (int k = 0; k <= n; k++) {
        long long c1 = binomial_coefficient(n, k);
        if (c1 == 0 && n > 0 && k > 0 && k < n) {
            return 0;
        }
        long long c2 = binomial_coefficient(n, k);
        if (c2 == 0 && n > 0 && k > 0 && k < n) {
            return 0;
        }
        if (c1 > __LLONG_MAX__ - c2) {
            return 0;
        }
        sum += c1 * c2;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 60) {
        fprintf(stderr, "Error: n must be a non-negative integer <= 60.\n");
        return EXIT_FAILURE;
    }
    long long result = sum_of_product_binomial((int)val);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}