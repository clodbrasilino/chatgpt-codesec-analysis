#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

unsigned int set_leftmost_unset_bit(unsigned int n) {
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'UINT_MAX'
     *  'UINT_MAX' undeclared (first use in this function)
     */
    if (n == UINT_MAX) {
        return n;
    }
    unsigned int mask = 1U;
    while (mask && (n & mask)) {
        mask <<= 1;
    }
    return n | mask;
}

int main(int argc, char *argv[]) {
    unsigned int num = 18;
    unsigned int result = set_leftmost_unset_bit(num);
    printf("%u\n", result);
    return 0;
}