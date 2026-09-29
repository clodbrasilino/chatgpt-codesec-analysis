#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 28, got <no output>
  *  test case 1 failed: expected 153, got <no output>
  *  test case 2 failed: expected 496, got <no output>
  */

long long cube_sum_odd(int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9222615723651324400 + 796108265857241 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:407,execs:198,op:havoc,rep:14)
         */
        sum += odd * odd * odd;
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }
    printf("%lld\n", cube_sum_odd(n));
    return 0;
}