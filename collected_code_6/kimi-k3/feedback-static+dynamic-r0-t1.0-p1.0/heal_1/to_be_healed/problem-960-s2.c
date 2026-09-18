#include <stdio.h>
#include <stdlib.h>

long long countTilings(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    
    long long *dp = (long long *)malloc((n + 1) * sizeof(long long));
    if (dp == NULL) {
        return -1;
    }
    
    dp[0] = 1;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7540113804746346429 + 4660046610375530309 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:285,execs:141,op:havoc,rep:11)
         */
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    long long result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    int n;
    printf("Enter the length of the board (n): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    long long result = countTilings(n);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Number of ways to tile 2 x %d board: %lld\n", n, result);
    return 0;
}