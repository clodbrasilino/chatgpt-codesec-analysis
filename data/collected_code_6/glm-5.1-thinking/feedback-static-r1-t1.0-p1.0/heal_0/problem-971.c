#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c) {
    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    int *dp = malloc(((size_t)n + 1) * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = -1;
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
    int result = dp[n] >= 0 ? dp[n] : 0;
    free(dp);
    return result;
}

int main(void) {
    int n = 7;
    int a = 5;
    int b = 2;
    int c = 5;
    int result = max_segments(n, a, b, c);
    printf("%d\n", result);
    return 0;
}