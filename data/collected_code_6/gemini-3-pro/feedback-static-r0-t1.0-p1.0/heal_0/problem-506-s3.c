#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_permutation(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }

    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        result *= (unsigned long long)(n - i);
    }

    return result;
}

int main() {
    int n, k;
    unsigned long long result;

    if (scanf("%d %d", &n, &k) != 2) {
        return EXIT_FAILURE;
    }

    result = calculate_permutation(n, k);

    if (result == 0 && (n < 0 || k < 0 || k > n)) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}