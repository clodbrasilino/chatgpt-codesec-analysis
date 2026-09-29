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
    unsigned long long dx = (x1 > x2) ? (unsigned long long)x1 - (unsigned long long)x2 : (unsigned long long)x2 - (unsigned long long)x1;
    unsigned long long dy = (y1 > y2) ? (unsigned long long)y1 - (unsigned long long)y2 : (unsigned long long)y2 - (unsigned long long)y1;
    
    unsigned long long g = gcd_ull(dx, dy);
    
    return (g == 0) ? 0 : (long long)(g - 1);
}

int main(void) {
    long long x1 = 0;
    long long y1 = 0;
    long long x2 = 5;
    long long y2 = 5;

    long long result = count_internal_points(x1, y1, x2, y2);

    if (printf("%lld\n", result) < 0) {
        return 1;
    }

    return 0;
}