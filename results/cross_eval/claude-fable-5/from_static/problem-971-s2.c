#include <stdio.h>
#include <stdlib.h>

static int max_segments(int n, int a, int b, int c)
{
    int *dp;
    int i;
    int result;

    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return -1;
    }

    dp = malloc((size_t)(n + 1) * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;
    for (i = 1; i <= n; i++) {
        dp[i] = -1;
    }

    for (i = 1; i <= n; i++) {
        if (i >= a && dp[i - a] != -1 && dp[i - a] + 1 > dp[i]) {
            dp[i] = dp[i - a] + 1;
        }
        if (i >= b && dp[i - b] != -1 && dp[i - b] + 1 > dp[i]) {
            dp[i] = dp[i - b] + 1;
        }
        if (i >= c && dp[i - c] != -1 && dp[i - c] + 1 > dp[i]) {
            dp[i] = dp[i - c] + 1;
        }
    }

    result = dp[n];
    free(dp);
    return result;
}

int main(void)
{
    int n;
    int a;
    int b;
    int c;
    int result;

    printf("Enter n, a, b, c: ");
    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = max_segments(n, a, b, c);
    if (result < 0) {
        fprintf(stderr, "No valid segmentation possible or invalid parameters\n");
        return EXIT_FAILURE;
    }

    printf("Maximum number of segments: %d\n", result);
    return EXIT_SUCCESS;
}