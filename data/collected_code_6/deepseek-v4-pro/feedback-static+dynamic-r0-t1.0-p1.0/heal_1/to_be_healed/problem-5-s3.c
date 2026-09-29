#include <stdio.h>
#include <stdlib.h>

int domino_tilings_3xn(int n) {
    if (n < 0) return 0;
    if (n % 2 != 0) return 0;
    
    int *dp = (int*)malloc((n + 1) * sizeof(int));
    if (dp == NULL) return 0;
    
    dp[0] = 1;
    if (n >= 1) dp[1] = 0;
    
    for (int i = 2; i <= n; i++) {
        if (i % 2 != 0) {
            dp[i] = 0;
        } else {
            dp[i] = 4 * dp[i - 2] - dp[i - 4];
        }
    }
    
    int result = dp[n];
    free(dp);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:266,execs:136,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter board width n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int ways = domino_tilings_3xn(n);
    printf("Number of ways to tile 3x%d board: %d\n", n, ways);
    
    return 0;
}