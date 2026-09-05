#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }

    if (k == 0 || k == n) {
        return 1;
    }

    if (k > n - k) {
        k = n - k;
    }

    unsigned long long res = 1;

    for (int i = 1; i <= k; i++) {
        if (res > ULLONG_MAX / (unsigned long long)(n - k + i)) {
            return 0;
        }
        res *= (unsigned long long)(n - k + i);
        res /= i;
    }

    return res;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        return 1;
    }

    char *endptr_n;
    errno = 0;
    long n_l = strtol(argv[1], &endptr_n, 10);
    if (errno != 0 || *endptr_n != '\0' || n_l < 0 || n_l > INT_MAX) {
        return 1;
    }

    char *endptr_k;
    errno = 0;
    long k_l = strtol(argv[2], &endptr_k, 10);
    if (errno != 0 || *endptr_k != '\0' || k_l < 0 || k_l > INT_MAX) {
        return 1;
    }

    int n = (int)n_l;
    int k = (int)k_l;

    unsigned long long result = binomial_coefficient(n, k);

    printf("%llu\n", result);

    return 0;
}