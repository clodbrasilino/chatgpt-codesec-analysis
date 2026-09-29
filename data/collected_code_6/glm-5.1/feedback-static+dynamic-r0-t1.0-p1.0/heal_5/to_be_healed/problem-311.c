#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 31
  *  test case 0 failed: expected 14, got 26
  *  test case 1 failed: expected 14, got 28
  */

unsigned int set_leftmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }
    unsigned int x = n;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return n | (x + 1);
}

int main(void) {
    unsigned int val;
    while (scanf("%u", &val) == 1) {
        printf("%u\n", set_leftmost_unset_bit(val));
    }
    return 0;
}