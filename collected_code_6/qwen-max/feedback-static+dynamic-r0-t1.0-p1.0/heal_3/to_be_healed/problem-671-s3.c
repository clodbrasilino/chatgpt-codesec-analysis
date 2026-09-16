#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 23, got 2
  *  test case 2 failed: expected 15, got 16
  *  test case 1 failed: expected 15, got 4
  */

uint32_t set_right_most_unset_bit(uint32_t n) {
    return (n | (n + 1)) & -((int32_t)(n + 1));
}

int main() {
    uint32_t n = 0b101010;
    n = set_right_most_unset_bit(n);
    printf("%u\n", n);
    return 0;
}