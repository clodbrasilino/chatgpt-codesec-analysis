#include <stdio.h>
#include <stdlib.h>

int e(int n, int k, int** memo) {
    if (k == 0 || k == n) return 1;
    if (k > n) return 0;
    if (memo[n][k] != -1) return memo[n][k];
    memo[n][k] = e(n-1, k-1, memo) + e(n-1, k, memo) + e(n-1, k+1, memo);
    return memo[n][k];
}

int main() {
    int n, k;
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2) {
        return 1;
    }
    int** memo = (int**)malloc((n+1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        memo[i] = (int*)calloc(k+2, sizeof(int));
        for (int j = 0; j <= k+1; j++) {
            memo[i][j] = -1;
        }
    }
    printf("e(%d, %d) = %d\n", n, k, e(n, k, memo));
    for (int i = 0; i <= n; i++) {
        free(memo[i]);
    }
    free(memo);
    return 0;
}