#include <stdio.h>
#include <stdlib.h>

long long count_tilings(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 1;
    }
    
    long long *dp = malloc((n + 1) * sizeof(long long));
    if (dp == NULL) {
        return -1;
    }
    
    dp[0] = 1;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7540113804746346429 + 4660046610375530309 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:264,execs:130,op:havoc,rep:3)
         */
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    long long result = dp[n];
    free(dp);
    dp = NULL;
    
    return result;
}

int main(void) {
    int n;
    
    printf("Enter the length of the board (2 x n): ");
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Error: Board length must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_tilings(n);
    
    if (result < 0) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of ways to tile 2 x %d board: %lld\n", n, result);
    
    return EXIT_SUCCESS;
}