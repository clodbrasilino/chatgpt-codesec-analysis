#include <stdio.h>
#include <stdlib.h>

unsigned long long count_tiling_ways(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0 || n == 1) {
        return 1;
    }

    unsigned long long *dp = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    unsigned long long result = dp[n];
    free(dp);

    return result;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Input must not be negative\n");
        return EXIT_FAILURE;
    }

    unsigned long long ways = count_tiling_ways(n);
    printf("%llu\n", ways);

    return EXIT_SUCCESS;
}