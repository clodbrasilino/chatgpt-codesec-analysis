#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int e(int n, int k, long** memo) {
    if (k == 0 || k == n) return 1;
    if (k > n) return 0;
    if (memo[n][k] != -1) return memo[n][k];
    /* Possible weaknesses found:
     * ASan: stack-overflow (AFL crash: id:000002,sig:11,src:000001,time:51480,execs:1019,op:havoc,rep:3)
     */
    memo[n][k] = e(n-1, k-1, memo) + e(n-1, k, memo) + e(n-1, k+1, memo);
    if (memo[n][k] > INT_MAX) return INT_MAX;
    return memo[n][k];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:7929,execs:216,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n, k;
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2) {
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