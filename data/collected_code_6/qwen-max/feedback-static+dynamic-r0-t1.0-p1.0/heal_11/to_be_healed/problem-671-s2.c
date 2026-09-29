#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 31
  */

uint32_t set_right_most_unset_bit(uint32_t n) {
    if (n == 0) return 1;
    if (n == 0xFFFFFFFF) return n;
    n |= (n + 1) & (~n);
    return n;
}

int main() {
    uint32_t num = 0b1010;
    uint32_t result = set_right_most_unset_bit(num);
    printf("Original: %u, After setting right most unset bit: %u\n", num, result);

    num = 0b1111;
    result = set_right_most_unset_bit(num);
    printf("Original: %u, After setting right most unset bit: %u\n", num, result);

    num = 0b1110;
    result = set_right_most_unset_bit(num);
    printf("Original: %u, After setting right most unset bit: %u\n", num, result);

    num = 0b11111111111111111111111111111111;
    result = set_right_most_unset_bit(num);
    printf("Original: %u, After setting right most unset bit: %u\n", num, result);

    num = 0b11111111111111111111111111111110;
    result = set_right_most_unset_bit(num);
    printf("Original: %u, After setting right most unset bit: %u\n", num, result);

    return 0;
}