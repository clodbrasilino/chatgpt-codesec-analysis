#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long factorial(int n) {
    unsigned long long res = 1;
    if (n < 0) return 0;
    for (int i = 1; i <= n; i++) {
        if (res > ULLONG_MAX / i) return 0;
        res *= i;
    }
    return res;
}

unsigned long long rencontres_number(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    if (n == 0 && k == 0) return 1;
    if (n == 0) return 0;
    unsigned long long fact = factorial(n - k);
    if (fact == 0 && (n - k) > 0) return 0;
    unsigned long long subfactorial = 1;
    unsigned long long term = 1;
    for (int i = 1; i <= n - k; i++) {
        if (term > ULLONG_MAX / (n - k)) {
            subfactorial = 0;
            break;
        }
        term = term * (n - k);
        if (i % 2 == 1) {
            if (subfactorial < term / i) {
                subfactorial = 0;
                break;
            }
            subfactorial -= term / i;
        } else {
            if (subfactorial > ULLONG_MAX - term / i) {
                subfactorial = 0;
                break;
            }
            subfactorial += term / i;
        }
    }
    return fact * subfactorial;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    char *endptr_n;
    char *endptr_k;
    long val_n = strtol(argv[1], &endptr_n, 10);
    long val_k = strtol(argv[2], &endptr_k, 10);
    if (*endptr_n != '\0' || *endptr_k != '\0' || val_n < 0 || val_k < 0 || val_n > INT_MAX || val_k > INT_MAX) {
        fprintf(stderr, "n and k must be non-negative integers within valid range\n");
        return 1;
    }
    int n = (int)val_n;
    int k = (int)val_k;
    unsigned long long res = rencontres_number(n, k);
    printf("%llu\n", res);
    return 0;
}