#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int e(int n, int k, long** memo) {
    if (k == 0 || k == n) return 1;
    if (k > n) return 0;
    if (memo[n][k] != -1) return memo[n][k];
    memo[n][k] = e(n-1, k-1, memo) + e(n-1, k, memo) + e(n-1, k+1, memo);
    if (memo[n][k] > INT_MAX) return INT_MAX;
    return memo[n][k];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:282,execs:161,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n, k;
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2) {
        return 1;
    }
    long** memo = (long**)malloc((n+1) * sizeof(long*));
    for (int i = 0; i <= n; i++) {
        /* Possible weaknesses found:
         * ASan: calloc (AFL crash: id:000002,sig:06,src:000003,time:38828,execs:817,op:havoc,rep:1)
         */
        memo[i] = (long*)calloc(k+2, sizeof(long));
        for (int j = 0; j <= k+1; j++) {
            memo[i][j] = -1;
        }
    }
    /* Possible weaknesses found:
     *  %ld in format string (no. 3) requires 'long' but the argument type is 'signed int'. [invalidPrintfArgType_sint]
     */
    printf("e(%d, %d) = %ld\n", n, k, e(n, k, memo));
    for (int i = 0; i <= n; i++) {
        free(memo[i]);
    }
    free(memo);
    return 0;
}