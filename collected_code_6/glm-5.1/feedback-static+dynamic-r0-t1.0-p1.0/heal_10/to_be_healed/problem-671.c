#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 31
  */

unsigned int set_rightmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }
    return n | ((~n) & (-(~n)));
}

int main(void) {
    unsigned int num = 10;
    unsigned int result = set_rightmost_unset_bit(num);
    printf("%u\n", result);

    num = 7;
    result = set_rightmost_unset_bit(num);
    printf("%u\n", result);

    result = set_rightmost_unset_bit(UINT_MAX);
    printf("%u\n", result);

    return 0;
}