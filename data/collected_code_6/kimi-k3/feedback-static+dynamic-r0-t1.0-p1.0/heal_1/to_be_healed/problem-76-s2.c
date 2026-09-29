#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5, got <no output>
  *  test case 0 failed: expected 20, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

long long count_squares(long long m, long long n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    
    if (m < n) {
        long long temp = m;
        m = n;
        n = temp;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 12 * 9223372036854775803 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:6589,execs:3067,op:havoc,rep:1)
     * UBSan: signed integer overflow: 111222 * 999999999399999667 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:237,execs:129,op:havoc,rep:16)
     * UBSan: signed integer overflow: 4444444444 * 4444444445 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:3045,execs:1409,op:havoc,rep:5)
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:6589,execs:3067,op:havoc,rep:1)
     * UBSan: signed integer overflow: 1306342346537361964 * 1333328888888889 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:3045,execs:1409,op:havoc,rep:5)
     */
    return n * (n + 1) * (3 * m - n + 1) / 6;
}

int main(void) {
    long long m, n;
    
    if (scanf("%lld %lld", &m, &n) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", count_squares(m, n));
    
    return EXIT_SUCCESS;
}