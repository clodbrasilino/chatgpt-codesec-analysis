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

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    if (n < 0 || k < 0) {
        fprintf(stderr, "n and k must be non-negative\n");
        return 1;
    }
    unsigned long long res = rencontres_number(n, k);
    printf("%llu\n", res);
    return 0;
}