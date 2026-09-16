#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 23, got <no output>
  *  test case 2 failed: expected 15, got <no output>
  *  test case 1 failed: expected 15, got <no output>
  */

unsigned int set_rightmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }
    return n | (n + 1);
}

int main(void) {
    unsigned int val = 0b1010;
    printf("%u\n", set_rightmost_unset_bit(val));
    return 0;
}