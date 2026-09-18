#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int findMinSquares(int n, int *dp) {
    if (n <= 3) return n;
    if (dp[n] != INT_MAX) return dp[n];

    for (int i = 1; i * i <= n; i++) {
        int res = 1 + findMinSquares(n - i * i, dp);
        if (res < dp[n]) dp[n] = res;
    }

    return dp[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000003,time:1346,execs:376,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }

    if (n > 0) {
        int *dp = (int *)malloc((n + 1) * sizeof(int));
        if (dp == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }

        for (int i = 0; i <= n; i++) {
            dp[i] = INT_MAX;
        }
        dp[0] = 0;

        int result = findMinSquares(n, dp);
        printf("Minimum number of squares: %d\n", result);

        free(dp);
    } else {
        printf("Minimum number of squares: %d\n", n);
    }
    return 0;
}