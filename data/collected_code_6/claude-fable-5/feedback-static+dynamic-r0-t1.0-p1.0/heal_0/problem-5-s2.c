#include <stdio.h>
#include <stdlib.h>

long long countWays(int n);

long long countWays(int n)
{
    long long *dp;
    long long result;
    int i;

    if (n < 0) {
        return 0;
    }

    if (n % 2 != 0) {
        return 0;
    }

    if (n == 0) {
        return 1;
    }

    if (n == 2) {
        return 3;
    }

    dp = malloc((size_t)(n + 1) * sizeof(long long));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i <= n; i++) {
        dp[i] = 0;
    }

    dp[0] = 1;
    dp[2] = 3;

    for (i = 4; i <= n; i += 2) {
        dp[i] = 4 * dp[i - 2] - dp[i - 4];
    }

    result = dp[n];
    free(dp);
    dp = NULL;

    return result;
}

int main(void)
{
    int n;
    long long ways;

    printf("Enter the value of n for a 3 x n board: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }

    if (n > 40) {
        fprintf(stderr, "n too large, result would overflow\n");
        return EXIT_FAILURE;
    }

    ways = countWays(n);
    printf("Number of ways to fill a 3 x %d board: %lld\n", n, ways);

    return EXIT_SUCCESS;
}