#include <stdio.h>
#include <limits.h>

int maxSegments(int n, int a, int b, int c) {
    /* Possible weaknesses found:
     * ASan: stack-overflow (AFL crash: id:000005,sig:06,src:000001,time:1100,execs:444,op:havoc,rep:1)
     * UBSan: variable length array bound evaluates to non-positive value -2144822158 (AFL crash: id:000005,sig:06,src:000001,time:1100,execs:444,op:havoc,rep:1)
     */
    int dp[n + 1];
    
    for (int i = 0; i <= n; i++) {
        dp[i] = INT_MIN;
    }
    
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         * ASan: dynamic-stack-buffer-overflow (AFL crash: id:000004,sig:06,src:000001,time:824,execs:341,op:havoc,rep:4)
         * UBSan: index 8 out of bounds for type 'int[n + 1]' (AFL crash: id:000004,sig:06,src:000001,time:824,execs:341,op:havoc,rep:4)
         */
        if (i >= a && dp[i - a] != INT_MIN) {
            dp[i] = dp[i - a] + 1;
        }
        /* Possible weaknesses found:
         * UBSan: index 8 out of bounds for type 'int[n + 1]' (AFL crash: id:000006,sig:06,src:000001,time:5581,execs:2518,op:havoc,rep:1)
         * ASan: dynamic-stack-buffer-overflow (AFL crash: id:000006,sig:06,src:000001,time:5581,execs:2518,op:havoc,rep:1)
         */
        if (i >= b && dp[i - b] != INT_MIN && dp[i - b] + 1 > dp[i]) {
            dp[i] = dp[i - b] + 1;
        }
        /* Possible weaknesses found:
         * ASan: dynamic-stack-buffer-overflow (AFL crash: id:000007,sig:06,src:000038,time:33129,execs:14556,op:havoc,rep:2)
         * UBSan: index 73 out of bounds for type 'int[n + 1]' (AFL crash: id:000007,sig:06,src:000038,time:33129,execs:14556,op:havoc,rep:2)
         */
        if (i >= c && dp[i - c] != INT_MIN && dp[i - c] + 1 > dp[i]) {
            dp[i] = dp[i - c] + 1;
        }
    }
    
    return dp[n] == INT_MIN ? -1 : dp[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000001,time:258,execs:114,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n, a, b, c;
    
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter a, b, c: ");
    scanf("%d %d %d", &a, &b, &c);
    
    int result = maxSegments(n, a, b, c);
    
    if (result == -1) {
        printf("Cannot form segments\n");
    } else {
        printf("Maximum segments: %d\n", result);
    }
    
    return 0;
}