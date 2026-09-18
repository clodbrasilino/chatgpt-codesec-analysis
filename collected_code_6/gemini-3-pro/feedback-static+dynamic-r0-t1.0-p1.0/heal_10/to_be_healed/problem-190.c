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
    return (x < 0) ? (unsigned long long)(-(x + 1)) + 1 : (unsigned long long)x;
}

/* Possible weaknesses found:
 *  to match this '{'
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 */
unsigned long long count_internal_points(long long x1, long long y1, long long x2, long long y2) {
    unsigned long long b1 = gcd_ull(get_abs(x1), get_abs(y1));
    unsigned long long b2 = gcd_ull(get_abs(x2), get_abs(y2));
    
    unsigned long long dx = (x1 > x2) ? (unsigned long long)x1 - (unsigned long long)x2 : (unsigned long long)x2 - (unsigned long long)x1;
    unsigned long long dy = (y1 > y2) ? (unsigned long long)y1 - (unsigned long long)y2 : (unsigned long long)y2 - (unsigned long long)y1;
    unsigned long long b3 = gcd_ull(dx, dy);
    
    unsigned long long B = b1 + b2 + b3;
    
    /* Possible weaknesses found:
     *  expected ';' at end of declaration
     *  expected declaration or statement at end of input
     *  expected identifier or '(' at end of input
     *  expected identifier or '('
     *  expected '}'
     */
    long long p1_h = 0,