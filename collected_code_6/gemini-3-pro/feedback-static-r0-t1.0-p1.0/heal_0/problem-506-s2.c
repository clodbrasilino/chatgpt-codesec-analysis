#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_permutation(int n, int k) {
    if (k < 0 || n < 0 || k > n) {
        return 0;
    }
    
    unsigned long long result = 1;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
    }
    
    return result;
}

int main(void) {
    int n = 0;
    int k = 0;

    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || k < 0) {
        fprintf(stderr, "Values must be non-negative\n");
        return EXIT_FAILURE;
    }

    unsigned long long p = calculate_permutation(n, k);
    printf("%llu\n", p);

    return EXIT_SUCCESS;
}