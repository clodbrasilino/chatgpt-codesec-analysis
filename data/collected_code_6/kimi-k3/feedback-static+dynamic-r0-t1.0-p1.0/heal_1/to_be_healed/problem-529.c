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
    if (n == 0) return 2;
    if (n == 1) return 1;
    
    long long prev2 = 2;
    long long prev1 = 1;
    long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * 4611686018427387905 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:50,execs:38,op:havoc,rep:12)
         * UBSan: signed integer overflow: 9223372036854775807 - -9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:50,execs:38,op:havoc,rep:12)
         */
        if (prev1 > LLONG_MAX - 2 * prev2) {
            errno = ERANGE;
            return -1;
        }
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    long long result = jacobsthal_lucas(n);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Result overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}