#include <stdio.h>
#include <stdlib.h>

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
         * UBSan: signed integer overflow: -2704893685957753274 + -6789648723593944064 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:226,execs:132,op:havoc,rep:6)
         * UBSan: signed integer overflow: 5743572120 * 5743572120 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:226,execs:132,op:havoc,rep:6)
         * UBSan: signed integer overflow: 6646215757681299270 + 4857445984927644900 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:2468,execs:1187,op:havoc,rep:3)
         */
        total += dp[k] * dp[k];
    }
    
    free(dp);
    return total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000003,time:278,execs:157,op:havoc,rep:16; likely memory-safety defect
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