#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_N 100

int64_t count_ways(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    if (n == 2) return 2;

    int64_t *dp = (int64_t *)malloc((n + 1) * sizeof(int64_t));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }

    int64_t result = dp[n];
    free(dp);
    return result;
}

int64_t solve_tiling(int n) {
    if (n < 0) {
        fprintf(stderr, "Invalid input: n must be non-negative\n");
        return -1;
    }
    if (n > MAX_N) {
        fprintf(stderr, "Invalid input: n too large\n");
        return -1;
    }
    return count_ways(n);
}

int main(void) {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int64_t ways = solve_tiling(n);
    if (ways != -1) {
        printf("Number of ways to tile 2x%d board: %lld\n", n, ways);
    }
    return EXIT_SUCCESS;
}