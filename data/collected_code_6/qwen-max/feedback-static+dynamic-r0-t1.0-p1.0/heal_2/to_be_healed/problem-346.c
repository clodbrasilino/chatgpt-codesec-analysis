#include <stdio.h>
#include <stdlib.h>

int e(int n, int k, int** memo) {
    if (k == 0 || k == n) return 1;
    if (k > n) return 0;
    /* Possible weaknesses found:
     * ASan: heap-buffer-overflow (AFL crash: id:000001,sig:06,src:000002,time:54012,execs:1311,op:havoc,rep:5)
     */
    if (memo[n][k] != -1) return memo[n][k];
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2083702528 + 619222008 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:54012,execs:1311,op:havoc,rep:5)
     * UBSan: signed integer overflow: 1440367757 + 1528186493 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:54012,execs:1311,op:havoc,rep:5)
     */
    memo[n][k] = e(n-1, k-1, memo) + e(n-1, k, memo) + e(n-1, k+1, memo);
    return memo[n][k];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:316,execs:163,op:havoc,rep:1; likely memory-safety defect
  */

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