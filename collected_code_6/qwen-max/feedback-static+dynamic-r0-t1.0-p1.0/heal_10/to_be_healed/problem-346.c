#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int e(int n, int k, long** memo) {
    if (k == 0 || k == n) return 1;
    if (k > n) return 0;
    /* Possible weaknesses found:
     * ASan: heap-buffer-overflow (AFL crash: id:000001,sig:06,src:000001,time:907,execs:343,op:havoc,rep:2)
     */
    if (memo[n][k] != -1) return memo[n][k];
    
    int result = 0;
    /* Possible weaknesses found:
     * ASan: stack-overflow (AFL crash: id:000002,sig:11,src:000001,time:8687,execs:583,op:havoc,rep:4)
     */
    if (n-1 >= 0 && k-1 >= 0) result += e(n-1, k-1, memo);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2113365664 + 647785238 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:907,execs:343,op:havoc,rep:2)
     */
    if (n-1 >= 0) result += e(n-1, k, memo);
    if (k+1 <= n && n-1 >= 0) result += e(n-1, k+1, memo);
    if (result > INT_MAX) return INT_MAX;
    memo[n][k] = result;
    return memo[n][k];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:508,execs:212,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2 || n < 0 || k < 0) {
        return 1;
    }
    long** memo = (long**)malloc((n+1) * sizeof(long*));
    if (memo == NULL) {
        return 1;
    }
    for (int i = 0; i <= n; i++) {
        memo[i] = (long*)calloc(k+1, sizeof(long));
        if (memo[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(memo[j]);
            }
            free(memo);
            return 1;
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
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