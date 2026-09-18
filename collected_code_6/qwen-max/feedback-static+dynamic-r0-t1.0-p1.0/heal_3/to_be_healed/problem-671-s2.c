#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 31
  */

uint32_t set_right_most_unset_bit(uint32_t n) {
    if (n == 0) return 1; // Special case: all bits are 0
    if (n == 0xFFFFFFFF) return 0; // All bits are 1, no unset bit to set
    n |= n + 1; // Set the rightmost unset bit
    return n;
}

int main() {
    uint32_t num = 0b1010;
    uint32_t result = set_right_most_unset_bit(num);
    printf("Original: %u, After setting right most unset bit: %u\n", num, result);
    
    num = 0b1111;
    result = set_right_most_unset_bit(num);
    printf("Original: %u, After setting right most unset bit: %u\n", num, result);
    
    return 0;
}