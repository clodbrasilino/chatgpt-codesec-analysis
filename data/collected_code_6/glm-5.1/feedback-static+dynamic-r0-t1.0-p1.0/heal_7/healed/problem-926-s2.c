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

unsigned long long subfactorial(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (n == 1) return 0;
    unsigned long long a = 1;
    unsigned long long b = 0;
    for (int i = 2; i <= n; i++) {
        unsigned long long temp = (i - 1) * (a + b);
        if (a > ULLONG_MAX - b) return 0;
        if ((a + b) > ULLONG_MAX / (i - 1)) return 0;
        temp = (i - 1) * (a + b);
        a = b;
        b = temp;
    }
    return b;
}

unsigned long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (k > n - k) k = n - k;
    unsigned long long res = 1;
    for (int i = 1; i <= k; i++) {
        if (res > ULLONG_MAX / (n - k + i)) return 0;
        res *= (n - k + i);
        if (res % i != 0) return 0;
        res /= i;
    }
    return res;
}

unsigned long long rencontres_number(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    if (n == 0 && k == 0) return 1;
    unsigned long long bc = binomial_coefficient(n, k);
    unsigned long long subfact = subfactorial(n - k);
    if (bc == 0 || subfact == 0) return 0;
    if (bc > ULLONG_MAX / subfact) return 0;
    return bc * subfact;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "0\n");
        return 1;
    }
    long n_l = strtol(argv[1], NULL, 10);
    long k_l = strtol(argv[2], NULL, 10);
    if (n_l < 0 || n_l > INT_MAX || k_l < 0 || k_l > INT_MAX) {
        fprintf(stderr, "0\n");
        return 1;
    }
    int n = (int)n_l;
    int k = (int)k_l;
    unsigned long long res = rencontres_number(n, k);
    printf("%llu\n", res);
    return 0;
}