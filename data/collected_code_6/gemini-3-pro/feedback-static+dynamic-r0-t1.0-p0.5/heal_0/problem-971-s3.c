#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaximumSegments(int n, int a, int b, int c) {
    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return -1;
    }

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

int main() {
    int n = 17;
    int a = 2;
    int b = 11;
    int c = 3;

    int maxSegments = findMaximumSegments(n, a, b, c);
    
    if (maxSegments != -1) {
        printf("%d\n", maxSegments);
    } else {
        printf("Invalid input or memory allocation failed.\n");
    }

    return 0;
}