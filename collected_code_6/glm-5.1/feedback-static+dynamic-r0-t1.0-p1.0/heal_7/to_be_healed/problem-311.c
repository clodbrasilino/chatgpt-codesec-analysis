#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 14, got 11
  *  test case 2 failed: expected 15, got 31
  *  test case 1 failed: expected 14, got 13
  */

unsigned int set_leftmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }
    unsigned int mask = ~n;
    /* Possible weaknesses found:
     *  Opposite expression on both sides of '&='. [oppositeExpression]
     */
    mask &= -mask;
    return n | mask;
}

int main(void) {
    unsigned int val;
    while (scanf("%u", &val) == 1) {
        printf("%u\n", set_leftmost_unset_bit(val));
    }
    return 0;
}