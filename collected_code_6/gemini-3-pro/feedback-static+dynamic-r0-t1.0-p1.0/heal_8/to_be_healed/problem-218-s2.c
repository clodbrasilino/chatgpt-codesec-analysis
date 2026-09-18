#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 2
  */

long long min_operations(long long a, long long b) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 22222222222 - -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:10239,execs:1375,op:havoc,rep:3)
     */
    long long diff = a > b ? a - b : b - a;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775803 * 2 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:947,execs:155,op:havoc,rep:2)
     * UBSan: signed integer overflow: -9223372014632553586 * 2 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:10239,execs:1375,op:havoc,rep:3)
     */
    return (diff * 2 + 1) / 3; 
}

int main(void) {
    long long a, b;
    
    if (scanf("%lld %lld", &a, &b) == 2) {
        long long result = min_operations(a, b);
        printf("%lld\n", result);
    }
    
    return EXIT_SUCCESS;
}