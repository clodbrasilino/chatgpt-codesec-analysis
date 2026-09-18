#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int e(int n, int k, long** memo) {
    if (k == 0 || k == n) return 1;
    if (k > n) return 0;
    if (memo[n][k] != -1) return memo[n][k];
    if (n-1 < 0 || k-1 < 0 || k+1 > n) return 0;
    memo[n][k] = e(n-1, k-1, memo) + e(n-1, k, memo) + e(n-1, k+1, memo);
    if (memo[n][k] > INT_MAX) return INT_MAX;
    return memo[n][k];
}

int main() {
    int n, k;
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2 || n < 0 || k < 0) {
        return 1;
    }
    long** memo = (long**)malloc((n+1) * sizeof(long*));
    if (memo == NULL) {
        return 1;
    }
    for (int i = 0; i <= n; i++) {
        memo[i] = (long*)calloc(k+2, sizeof(long));
        if (memo[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(memo[j]);
            }
            free(memo);
            return 1;
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k+1; j++) {
            memo[i][j] = -1;
        }
    }
    printf("e(%d, %d) = %ld\n", n, k, (long)e(n, k, memo));
    for (int i = 0; i <= n; i++) {
        free(memo[i]);
    }
    free(memo);
    return 0;
}