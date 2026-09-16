#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long rencontres(unsigned int n, unsigned int k) {
    if (k > n) {
        return 0;
    }
    if (k == 0) {
        if (n == 0) {
            return 1;
        }
        if (n == 1) {
            return 0;
        }
        unsigned long long d0 = 1;
        unsigned long long d1 = 0;
        unsigned long long d2 = 0;
        unsigned int i;
        for (i = 2; i <= n; ++i) {
            d2 = (i - 1) * (d1 + d0);
            d0 = d1;
            d1 = d2;
        }
        return d1;
    }
    unsigned long long result = rencontres(n - k, 0);
    unsigned int i;
    for (i = 0; i < k; ++i) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

int main(void) {
    unsigned int n, k;
    if (scanf("%u %u", &n, &k) != 2) {
        return EXIT_FAILURE;
    }
    if (n > 20) {
        fprintf(stderr, "Input too large\n");
        return EXIT_FAILURE;
    }
    printf("%llu\n", rencontres(n, k));
    return EXIT_SUCCESS;
}