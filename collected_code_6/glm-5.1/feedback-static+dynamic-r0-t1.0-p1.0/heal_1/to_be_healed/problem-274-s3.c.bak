#include <stdio.h>
#include <stdlib.h>

long long sum_even_index_binomial_coefficients(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 1;
    }
    if (n % 2 == 0) {
        long long val = 1LL << (n - 1);
        long long c = 1;
        int i;
        for (i = 0; i < n / 2; i++) {
            c = c * (n - i) / (i + 1);
        }
        return val + c;
    } else {
        return 1LL << (n - 1);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        return 1;
    }
    n = atoi(argv[1]);
    if (n < 0) {
        return 1;
    }
    long long result = sum_even_index_binomial_coefficients(n);
    printf("%lld\n", result);
    return 0;
}