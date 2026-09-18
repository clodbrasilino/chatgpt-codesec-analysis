#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t count_sequences(int n, int m) {
    if (n == 0 || m == 0) return 1;
    int64_t *dp = (int64_t *)malloc((n + 1) * (m + 1) * sizeof(int64_t));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int j = 0; j <= m; ++j) dp[j] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i*(m+1) + j] = 0;
            for (int k = 1; k * 2 <= j; ++k) {
                dp[i*(m+1) + j] += dp[(i-1)*(m+1) + k];
            }
        }
    }
    int64_t result = 0;
    for (int j = 0; j <= m; ++j) {
        result += dp[n*(m+1) + j];
    }
    free(dp);
    return result;
}

int main() {
    int n, m;
    printf("Enter the length of the sequence (n): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input for n\n");
        return 1;
    }
    printf("Enter the maximum value in the sequence (m): ");
    if (scanf("%d", &m) != 1 || m < 0) {
        fprintf(stderr, "Invalid input for m\n");
        return 1;
    }
    int64_t result = count_sequences(n, m);
    printf("Number of sequences: %" PRId64 "\n", result);
    return 0;
}