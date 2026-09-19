#include <stdio.h>
#include <stdlib.h>

int find_max_segments(int n, int a, int b, int c) {
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    if (!dp) {
        return -1;
    }
    for (int i = 0; i <= n; i++) {
        dp[i] = -1;
    }
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (i >= a && dp[i - a] != -1) {
            if (dp[i] < dp[i - a] + 1) {
                dp[i] = dp[i - a] + 1;
            }
        }
        if (i >= b && dp[i - b] != -1) {
            if (dp[i] < dp[i - b] + 1) {
                dp[i] = dp[i - b] + 1;
            }
        }
        if (i >= c && dp[i - c] != -1) {
            if (dp[i] < dp[i - c] + 1) {
                dp[i] = dp[i - c] + 1;
            }
        }
    }
    int result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    int n, a, b, c;
    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4) {
        return EXIT_FAILURE;
    }
    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return EXIT_FAILURE;
    }
    int result = find_max_segments(n, a, b, c);
    if (result == -1) {
        printf("0\n");
    } else {
        printf("%d\n", result);
    }
    return EXIT_SUCCESS;
}