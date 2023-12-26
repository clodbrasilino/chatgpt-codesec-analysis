#include <stdio.h>
#include <stdlib.h>

int maxChainLength(const int pairs[][2], int n) {
    int* dp = (int*)malloc(n * sizeof(int));

    if (!dp) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (pairs[j][1] < pairs[i][0] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
        }
    }

    free(dp);
    return maxLength;
}

int main() {
    const int pairs[][2] = {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}};
    int n = sizeof(pairs) / sizeof(pairs[0]);

    int longestChain = maxChainLength(pairs, n);

    if(longestChain != -1) {
        printf("Longest chain length: %d\n", longestChain);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}