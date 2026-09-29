#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool canTile(int n, int m) {
    if (n <= 2 || m <= 2) {
        return n == m;
    }
    bool *dp = (bool *)calloc((n+1) * (m+1), sizeof(bool));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    dp[1 * (m + 1) + 1] = true;
    dp[2 * (m + 1) + 2] = true;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i * (m + 1) + j] = false;
            } else if (i >= 2 && j >= 2) {
                dp[i * (m + 1) + j] = (dp[(i-1) * (m + 1) + (j-1)] || dp[(i-2) * (m + 1) + j] || dp[i * (m + 1) + (j-2)]);
            }
        }
    }
    bool result = dp[n * (m + 1) + m];
    free(dp);
    return result;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n < 0 || m < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (canTile(n, m)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}