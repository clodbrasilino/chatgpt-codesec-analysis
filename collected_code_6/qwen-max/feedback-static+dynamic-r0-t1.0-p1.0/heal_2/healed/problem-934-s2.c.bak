#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long long delannoy_number(int n, int m) {
    if (n < 0 || m < 0) return -1;
    uint64_t dp[n+1][m+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1] + dp[i-1][j-1];
            }
        }
    }
    return dp[n][m];
}

int main() {
    int n, m;
    printf("Enter n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        printf("Invalid input.\n");
        return 1;
    }
    if (n < 0 || m < 0) {
        printf("Both n and m must be non-negative.\n");
        return 1;
    }
    long long result = delannoy_number(n, m);
    if (result == -1) {
        printf("Error calculating Delannoy number.\n");
        return 1;
    }
    printf("The Delannoy number D(%d, %d) is: %lld\n", n, m, result);
    return 0;
}