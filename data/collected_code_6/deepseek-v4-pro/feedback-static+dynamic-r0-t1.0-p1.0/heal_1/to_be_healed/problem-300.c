#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 6.0, got <no output>
  *  test case 0 failed: expected 2.0, got <no output>
  *  test case 2 failed: expected 20.0, got <no output>
  */

long long count_binary_sequences(int n) {
    if (n <= 0) {
        return 0;
    }
    
    long long *dp = (long long *)calloc(n + 1, sizeof(long long));
    if (dp == NULL) {
        return -1;
    }
    
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            dp[j] += dp[j - 1];
        }
    }
    
    long long total = 0;
    for (int k = 0; k <= n; k++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6646215757681299270 + 4857445984927644900 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:34876,execs:13659,op:havoc,rep:2)
         * UBSan: signed integer overflow: 6358402050 * 6358402050 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:4789,execs:1921,op:havoc,rep:4)
         * UBSan: signed integer overflow: 5060288580294794640 + 6933266088399950564 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:4789,execs:1921,op:havoc,rep:4)
         */
        total += dp[k] * dp[k];
    }
    
    free(dp);
    return total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:3969,execs:1660,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }
    
    long long result = count_binary_sequences(n);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("%lld\n", result);
    return 0;
}