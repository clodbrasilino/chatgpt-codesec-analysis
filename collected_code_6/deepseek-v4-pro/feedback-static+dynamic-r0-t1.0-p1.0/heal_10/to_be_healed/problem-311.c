#include <stdio.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 14, got 2147483658
  *  test case 1 failed: expected 14, got 2147483660
  *  test case 2 failed: expected 15, got 2147483663
  */

unsigned int set_leftmost_unset_bit(unsigned int num) {
    unsigned int mask = 1u << (sizeof(unsigned int) * CHAR_BIT - 1);
    
    if (num == 0) {
        return mask;
    }
    
    while (mask != 0u) {
        if ((num & mask) == 0u) {
            return num | mask;
        }
        mask >>= 1u;
    }
    
    return num;
}

int main(void) {
    unsigned int test_values[] = {0u, 1u, 0xFFFFFFFFu, 0x0F0F0F0Fu, 0x80000000u};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; ++i) {
        unsigned int input = test_values[i];
        unsigned int result = set_leftmost_unset_bit(input);
        printf("Input: 0x%08X, Result: 0x%08X\n", input, result);
    }
    
    return 0;
}