#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaximumSegments(int n, int a, int b, int c) {
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = -1;
    }

    dp[0] = 0;

    for (int i = 0; i <= n; i++) {
        if (dp[i] != -1) {
            if (i + a <= n) {
                dp[i + a] = max(dp[i + a], dp[i] + 1);
            }
            if (i + b <= n) {
                dp[i + b] = max(dp[i + b], dp[i] + 1);
            }
            if (i + c <= n) {
                dp[i + c] = max(dp[i + c], dp[i] + 1);
            }
        }
    }

    int result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    int n = 7;
    int a = 5;
    int b = 2;
    int c = 2;

    int max_segments = findMaximumSegments(n, a, b, c);

    if (max_segments != -1) {
        printf("%d\n", max_segments);
    } else {
        printf("Memory allocation failed or no segments can be formed.\n");
    }

    return 0;
}