#include <stdio.h>
#include <stdlib.h>

int count_sequences(int n, int m) {
    if (n == 0 || m <= 0) return 1;
    int *dp = (int *)malloc((n + 1) * (m + 1) * sizeof(int));
    for (int j = 1; j <= m; ++j) dp[j] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[(i-1)*(m+1) + j] = 0;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k * 2 <= j; ++k)
                dp[i*(m+1) + j] += dp[(i-1)*(m+1) + k];
    int result = 0;
    for (int j = 1; j <= m; ++j)
        result += dp[n*(m+1) + j];
    free(dp);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:4,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n, m;
    printf("Enter the length of the sequence (n): ");
    scanf("%d", &n);
    printf("Enter the maximum value in the sequence (m): ");
    scanf("%d", &m);
    int result = count_sequences(n, m);
    printf("Number of sequences: %d\n", result);
    return 0;
}