#include <stdio.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got <no output>
  *  test case 2 failed: expected 15, got <no output>
  *  test case 0 failed: expected 14, got <no output>
  */

unsigned int set_leftmost_unset_bit(unsigned int num) {
    unsigned int mask = 1u << (sizeof(unsigned int) * CHAR_BIT - 1);
    unsigned int result = num;
    
    while (mask != 0) {
        if ((num & mask) == 0) {
            result = num | mask;
            break;
        }
        mask >>= 1;
    }
    
    return result;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 0xFFFFFFFF, 0x0F0F0F0F, 0x80000000};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; ++i) {
        unsigned int input = test_values[i];
        unsigned int result = set_leftmost_unset_bit(input);
        printf("Input: 0x%08X, Result: 0x%08X\n", input, result);
    }
    
    return 0;
}