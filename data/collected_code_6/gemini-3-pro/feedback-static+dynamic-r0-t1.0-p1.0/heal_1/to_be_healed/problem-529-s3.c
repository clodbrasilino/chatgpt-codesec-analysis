#include <stdio.h>
#include <stdlib.h>

long long jacobsthal_lucas(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }
    
    long long prev2 = 2;
    long long prev1 = 1;
    long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * 4611686018427387905 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:316,execs:167,op:havoc,rep:1)
         */
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    long long result = jacobsthal_lucas(n);
    if (result == -1) {
        return 1;
    }
    
    printf("%lld\n", result);
    
    return 0;
}