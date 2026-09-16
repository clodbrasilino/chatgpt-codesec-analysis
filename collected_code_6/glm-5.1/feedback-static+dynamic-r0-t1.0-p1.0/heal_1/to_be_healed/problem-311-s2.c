#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 12
  *  test case 0 failed: expected 14, got 10
  */

unsigned int set_leftmost_unset_bit(unsigned int n) {
    /* Possible weaknesses found:
     *  Condition '~n==0' is always false [knownConditionTrueFalse]
     */
    if (~n == 0) {
        return n;
    }
    unsigned int mask = 1U << (sizeof(unsigned int) * 8 - 1);
    while (n & mask) {
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