#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5, got 4
  *  test case 2 failed: expected 17, got 22
  *  test case 0 failed: expected 31, got 53
  */

long long jacobsthal_lucas(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 4611686018427387905 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:373,execs:162,op:havoc,rep:4)
     */
    }
    if (n == 1) {
        return 1;
    }
    
    long long prev2 = 2;
    long long prev1 = 1;
    long long current = 0;
    int i;
    
    for (i = 2; i <= n; i++) {
        if (prev1 > (LLONG_MAX - prev2) / 2) {
            return -1;
        }
        current = 2 * prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

int main(void) {
    int n;
    long long result;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        return EXIT_FAILURE;
    }
    
    result = jacobsthal_lucas(n);
    
    if (result == -1) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}