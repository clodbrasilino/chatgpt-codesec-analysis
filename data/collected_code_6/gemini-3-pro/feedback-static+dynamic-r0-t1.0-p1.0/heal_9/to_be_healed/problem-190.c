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

unsigned long long get_abs(long long x) {
    return (x < 0) ? -(unsigned long long)x : (unsigned long long)x;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got 0
  *  test case 2 failed: expected 1, got 0
  *  test case 0 failed: expected 4, got 0
  */

long long count_internal_points(long long x1, long long y1, long long x2, long long y2) {
    unsigned long long b1 = gcd_ull(get_abs(x1), get_abs(y1));
    unsigned long long b2 = gcd_ull(get_abs(x2), get_abs(y2));
    
    unsigned long long dx = (x1 > x2) ? (unsigned long long)x1 - (unsigned long long)x2 : (unsigned long long)x2 - (unsigned long long)x1;
    unsigned long long dy = (y1 > y2) ? (unsigned long long)y1 - (unsigned long long)y2 : (unsigned long long)y2 - (unsigned long long)y1;
    unsigned long long b3 = gcd_ull(dx, dy);
    
    unsigned long long B = b1 + b2 + b3;
    
    __int128 p1 = (__int128)x1 * y2;
    __int128 p2 = (__int128)x2 * y1;
    __int128 area2 = p1 - p2;
    if (area2 < 0) area2 = -area2;
    
    if (area2 == 0) return 0;

    return (long long)((area2 - B + 2) / 2);
}

int main(void) {
    long long x1, y1, x2, y2;

    if (scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2) == 4) {
        long long result = count_internal_points(x1, y1, x2, y2);
        printf("%lld\n", result);
    }

    return 0;
}