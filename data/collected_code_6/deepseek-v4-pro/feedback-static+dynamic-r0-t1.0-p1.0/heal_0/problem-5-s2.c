#include <stdio.h>
#include <stdlib.h>

int domino_ways(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (n == 1) return 0;
    if (n % 2 != 0) return 0;

    int m = n / 2;
    int *dp = (int *)malloc((m + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 1;
    dp[1] = 3;
    for (int i = 2; i <= m; i++) {
        dp[i] = 4 * dp[i - 1] - dp[i - 2];
    }

    int result = dp[m];
    free(dp);
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int ways = domino_ways(n);
    if (ways == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Number of ways: %d\n", ways);
    return 0;
}