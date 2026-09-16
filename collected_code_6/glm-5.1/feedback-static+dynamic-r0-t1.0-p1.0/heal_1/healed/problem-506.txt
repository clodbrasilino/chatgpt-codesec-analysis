#include <stdio.h>
#include <stdlib.h>

unsigned long long permutation_coefficient(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    if (k == 0) {
        return 1;
    }
    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        if (__builtin_mul_overflow(result, (unsigned long long)(n - i), &result)) {
            return 0;
        }
    }
    return result;
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) {
        return EXIT_FAILURE;
    }
    unsigned long long res = permutation_coefficient(n, k);
    printf("%llu\n", res);
    return EXIT_SUCCESS;
}