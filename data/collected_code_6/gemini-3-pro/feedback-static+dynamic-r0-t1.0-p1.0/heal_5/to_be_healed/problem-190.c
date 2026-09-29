#include <stdio.h>
#include <stdlib.h>

unsigned long long gcd_ull(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got <no output>
  *  test case 1 failed: expected 1, got <no output>
  *  test case 0 failed: expected 4, got <no output>
  */

long long count_internal_points(long long x1, long long y1, long long x2, long long y2) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1 - -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000009,time:30000,execs:3320,op:havoc,rep:1)
     */
    unsigned long long dx = (x1 > x2) ? (unsigned long long)(x1 - x2) : (unsigned long long)(x2 - x1);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 - -222222222222 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000009,time:29795,execs:3299,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 - -222222222222222 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000010,time:34810,execs:3863,op:havoc,rep:3)
     */
    unsigned long long dy = (y1 > y2) ? (unsigned long long)(y1 - y2) : (unsigned long long)(y2 - y1);
    
    unsigned long long g = gcd_ull(dx, dy);
    
    return (g == 0) ? 0 : (long long)(g - 1);
}

int main(void) {
    long long x1, y1, x2, y2;

    if (scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2) != 4) {
        return 1;
    }

    long long result = count_internal_points(x1, y1, x2, y2);

    printf("%lld\n", result);

    return 0;
}