#include <stdio.h>
#include <stdlib.h>

int delannoy(int n, int m) {
    if (n == 0 || m == 0) return 1;
    int dp[n+1][m+1];
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < m + 1; ++j) {
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
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Delannoy number D(%d, %d) is %d\n", n, m, delannoy(n, m));
    return EXIT_SUCCESS;
}