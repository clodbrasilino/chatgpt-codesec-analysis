#include <stdio.h>
#include <stdlib.h>

int longest_increasing_subsequence(const int *seq, int n) {
    if (seq == NULL || n <= 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    int max_len = 1;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (seq[j] < seq[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }

    free(dp);
    return max_len;
}

int main() {
    int seq[] = {10, 22, 9, 33, 21, 50, 41, 60};
    int n = sizeof(seq) / sizeof(seq[0]);

    int result = longest_increasing_subsequence(seq, n);
    printf("%d\n", result);

    return 0;
}