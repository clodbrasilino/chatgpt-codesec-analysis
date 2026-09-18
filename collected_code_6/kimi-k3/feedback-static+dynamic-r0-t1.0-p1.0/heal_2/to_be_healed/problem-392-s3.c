#include <stdio.h>
#include <stdlib.h>

long long max_sum(long long n, long long *memo, long long memo_size) {
    if (n <= 0) {
        return 0;
    }
    if (n < memo_size && memo[n] != -1) {
        return memo[n];
    }
    
    long long sum = max_sum(n / 2, memo, memo_size) + 
                    max_sum(n / 3, memo, memo_size) + 
                    max_sum(n / 4, memo, memo_size) + 
                    max_sum(n / 5, memo, memo_size);
    
    long long result = (sum > n) ? sum : n;
    
    if (n < memo_size) {
        memo[n] = result;
    }
    
    return result;
}

long long solve(long long n) {
    /* Possible weaknesses found:
     *  Assuming that condition 'n<=0' is not redundant
     */
    if (n <= 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:7960,execs:259,op:havoc,rep:2)
     *  Assignment 'memo_size=n+1', assigned value is greater than 1
     */
    long long memo_size = n + 1;
    /* Possible weaknesses found:
     *  Condition 'memo_size<=0' is always false [knownConditionTrueFalse]
     *  Condition 'memo_size<=0' is always false
     */
    if (memo_size <= 0) {
        return n;
    }
    
    if ((unsigned long long)memo_size > (unsigned long long)SIZE_MAX / sizeof(long long)) {
        return n;
    }
    
    long long *memo = malloc((size_t)memo_size * sizeof(long long));
    if (memo == NULL) {
        return n;
    }
    
    for (long long i = 0; i < memo_size; i++) {
        memo[i] = -1;
    }
    
    long long result = max_sum(n, memo, memo_size);
    free(memo);
    
    return result;
}

int main(void) {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        return 1;
    }
    
    if (n < 0) {
        return 1;
    }
    
    printf("%lld\n", solve(n));
    
    return 0;
}