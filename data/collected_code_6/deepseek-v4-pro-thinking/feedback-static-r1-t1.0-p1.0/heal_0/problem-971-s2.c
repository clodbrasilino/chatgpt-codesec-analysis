#include <stdio.h>
#include <stdlib.h>

int maxSegments(int n, int a, int b, int c) {
    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return -1;
    }

    int *dp = (int *)malloc(((size_t)n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = -1;
    }

    for (int i = 1; i <= n; ++i) {
        if (i >= a && dp[i - a] != -1) {
            int val = dp[i - a] + 1;
            if (val > dp[i]) {
                dp[i] = val;
            }
        }
        if (i >= b && dp[i - b] != -1) {
            int val = dp[i - b] + 1;
            if (val > dp[i]) {
                dp[i] = val;
            }
        }
        if (i >= c && dp[i - c] != -1) {
            int val = dp[i - c] + 1;
            if (val > dp[i]) {
                dp[i] = val;
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
        return 1;
    }

    int result = maxSegments(n, a, b, c);
    printf("%d\n", result);
    return 0;
}