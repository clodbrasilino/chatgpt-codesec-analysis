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
        unsigned long long temp = b;
        if (temp > ULLONG_MAX / i) return 0;
        temp *= i;
        if (temp > ULLONG_MAX - a) return 0;
        temp += a;
        a = b;
        b = temp;
    }
    return b;
}

unsigned long long rencontres_number(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    if (n == 0 && k == 0) return 1;
    unsigned long long fact = factorial(n - k);
    if (fact == 0 && (n - k) > 0) return 0;
    unsigned long long subfact = subfactorial(n - k);
    if (subfact == 0 && (n - k) > 1) return 0;
    if (fact > ULLONG_MAX / subfact) return 0;
    return fact * subfact;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        printf("0\n");
        return 1;
    }
    long n_l = strtol(argv[1], NULL, 10);
    long k_l = strtol(argv[2], NULL, 10);
    if (n_l < 0 || n_l > INT_MAX || k_l < 0 || k_l > INT_MAX) {
        printf("0\n");
        return 1;
    }
    int n = (int)n_l;
    int k = (int)k_l;
    unsigned long long res = rencontres_number(n, k);
    printf("%llu\n", res);
    return 0;
}