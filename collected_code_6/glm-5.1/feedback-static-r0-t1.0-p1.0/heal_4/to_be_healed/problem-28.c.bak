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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return 1;
    }

    long n_l = strtol(argv[1], NULL, 10);
    long k_l = strtol(argv[2], NULL, 10);

    if (n_l < 0 || n_l > INT_MAX || k_l < 0 || k_l > INT_MAX) {
        return 1;
    }

    int n = (int)n_l;
    int k = (int)k_l;

    unsigned long long result = binomial_coefficient(n, k);

    printf("%llu\n", result);

    return 0;
}