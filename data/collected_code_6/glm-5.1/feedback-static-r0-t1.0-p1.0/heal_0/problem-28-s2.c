#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (n < 0 || k < 0) {
        exit(EXIT_FAILURE);
    }
    if (k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n / 2) {
        k = n - k;
    }
    unsigned long long res = 1;
    for (int i = 1; i <= k; i++) {
        if (res > (unsigned long long)(-1) / (n - k + i)) {
            exit(EXIT_FAILURE);
        }
        res *= (n - k + i);
        res /= i;
    }
    return res;
}

int main(void) {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) {
        return EXIT_FAILURE;
    }
    unsigned long long result = binomial_coefficient(n, k);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}