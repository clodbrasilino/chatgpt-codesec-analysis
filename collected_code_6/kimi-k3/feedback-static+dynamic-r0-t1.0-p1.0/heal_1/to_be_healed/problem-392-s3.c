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
    if (n <= 0) {
        return 0;
    }
    
    long long memo_size = n + 1;
    long long *memo = malloc(memo_size * sizeof(long long));
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:616,execs:264,op:havoc,rep:1; likely memory-safety defect
  */

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