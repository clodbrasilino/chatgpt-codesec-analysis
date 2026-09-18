#include <stdio.h>
#include <stdlib.h>

long long solve_tiling(int n) {
    if (n < 0) {
        return -1;
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
         * UBSan: signed integer overflow: 7540113804746346429 + 4660046610375530309 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:1297,execs:655,op:havoc,rep:7)
         */
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    long long result = dp[n];
    free(dp);

    return result;
}

int main() {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    long long ways = solve_tiling(n);

    if (ways == -1) {
        return 1;
    }

    printf("%lld\n", ways);

    return 0;
}