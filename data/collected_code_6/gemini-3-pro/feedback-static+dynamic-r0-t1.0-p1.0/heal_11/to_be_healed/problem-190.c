#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned long long gcd_ull(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long get_abs(long long x) {
    return (x < 0) ? (unsigned long long)(-(x + 1)) + 1 : (unsigned long long)x;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got <no output>
  *  test case 1 failed: expected 1, got <no output>
  *  test case 0 failed: expected 4, got <no output>
  */

unsigned long long count_internal_points(long long x1, long long y1, long long x2, long long y2) {
    unsigned long long b1 = gcd_ull(get_abs(x1), get_abs(y1));
    unsigned long long b2 = gcd_ull(get_abs(x2), get_abs(y2));
    
    unsigned long long dx = (x1 > x2) ? (unsigned long long)x1 - (unsigned long long)x2 : (unsigned long long)x2 - (unsigned long long)x1;
    unsigned long long dy = (y1 > y2) ? (unsigned long long)y1 - (unsigned long long)y2 : (unsigned long long)y2 - (unsigned long long)y1;
    unsigned long long b3 = gcd_ull(dx, dy);
    
    unsigned long long B = b1 + b2 + b3;
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 11 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:32465,execs:3488,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 * 4 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:6804,execs:735,op:havoc,rep:2)
     */
    long long cross_product = x1 * y2 - x2 * y1;
    unsigned long long double_area = get_abs(cross_product);
    
    unsigned long long internal_points = (double_area - B + 2) / 2;
    return internal_points;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:7406,execs:805,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    long long x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    
    if (scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2) == 4) {
        unsigned long long result = count_internal_points(x1, y1, x2, y2);
        printf("%llu\n", result);
    }
    
    return 0;
}