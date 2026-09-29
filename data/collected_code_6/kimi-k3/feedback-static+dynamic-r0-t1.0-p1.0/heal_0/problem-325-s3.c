#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minSquares(int n)
{
    if (n < 0) {
        return -1;
    }
    
    if (n == 0) {
        return 0;
    }
    
    int *dp = (int *)malloc((size_t)(n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        dp[i] = INT_MAX;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            int square = j * j;
            if (dp[i - square] != INT_MAX && dp[i - square] + 1 < dp[i]) {
                dp[i] = dp[i - square] + 1;
            }
        }
    }
    
    int result = dp[n];
    free(dp);
    dp = NULL;
    
    return result;
}

int main(void)
{
    int testCases[] = {12, 13, 25, 1, 0, 100};
    size_t numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (size_t i = 0; i < numTests; i++) {
        int n = testCases[i];
        int result = minSquares(n);
        
        if (result >= 0) {
            printf("Minimum squares for %d: %d\n", n, result);
        } else {
            printf("Error computing result for %d\n", n);
        }
    }
    
    return 0;
}