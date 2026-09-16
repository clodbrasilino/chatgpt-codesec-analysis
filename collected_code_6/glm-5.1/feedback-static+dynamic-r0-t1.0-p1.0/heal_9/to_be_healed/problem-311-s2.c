#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 14, got 2147483658
  *  test case 1 failed: expected 14, got 2147483660
  *  test case 2 failed: expected 15, got 2147483663
  */

unsigned int set_leftmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }
    unsigned int mask = 1U << (sizeof(unsigned int) * CHAR_BIT - 1);
    while ((n & mask) != 0) {
        mask >>= 1;
    }
    return n | mask;
}

int main(int argc, char *argv[]) {
    unsigned int num = 18;
    unsigned int result = set_leftmost_unset_bit(num);
    printf("%u\n", result);
    return 0;
}