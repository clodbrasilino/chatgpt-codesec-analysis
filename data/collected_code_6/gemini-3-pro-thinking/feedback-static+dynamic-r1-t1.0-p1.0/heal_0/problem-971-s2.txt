#include <stdio.h>
#include <stdlib.h>

int find_max_segments(int n, int a, int b, int c);

int find_max_segments(int n, int a, int b, int c) {
    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return -1;
    }

    int *dp = (int *)malloc((size_t)(n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = -1;
    }

    for (int i = 1; i <= n; i++) {
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

    int result = dp[n];
    free(dp);
    
    return result;
}

int main(void) {
    int n;
    int a;
    int b;
    int c;

    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4) {
        return 1;
    }

    int max_segments = find_max_segments(n, a, b, c);

    if (max_segments == -1) {
        return 1;
    }

    if (printf("%d\n", max_segments) < 0) {
        return 1;
    }

    return 0;
}