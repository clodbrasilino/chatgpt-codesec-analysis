#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxSegments(int n, int a, int b, int c) {
    if (n < 0) {
        return -1;
    }
    
    int *dp = malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i] = INT_MIN;
    }
    
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        if (i >= a && dp[i - a] != INT_MIN) {
            dp[i] = dp[i - a] + 1;
        }
        /* Possible weaknesses found:
         * ASan: BUS (AFL crash: id:000002,sig:11,src:000000,time:44663,execs:11317,op:havoc,rep:12)
         */
        if (i >= b && dp[i - b] != INT_MIN && dp[i - b] + 1 > dp[i]) {
            dp[i] = dp[i - b] + 1;
        }
        /* Possible weaknesses found:
         * ASan: BUS (AFL crash: id:000001,sig:11,src:000000,time:39385,execs:9486,op:havoc,rep:13)
         */
        if (i >= c && dp[i - c] != INT_MIN && dp[i - c] + 1 > dp[i]) {
            dp[i] = dp[i - c] + 1;
        }
    }
    
    int result = dp[n] == INT_MIN ? -1 : dp[n];
    free(dp);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000000,time:26311,execs:4348,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    int n, a, b, c;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Enter a, b, c: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = maxSegments(n, a, b, c);
    
    if (result == -1) {
        printf("Cannot form segments\n");
    } else {
        printf("Maximum segments: %d\n", result);
    }
    
    return 0;
}