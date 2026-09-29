#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 2147483660
  *  test case 0 failed: expected 14, got 2147483658
  *  test case 2 failed: expected 15, got 2147483663
  */

unsigned int set_leftmost_unset_bit(unsigned int num) {
    unsigned int mask = 1u << (sizeof(unsigned int) * 8 - 1);
    
    while (mask != 0) {
        if ((num & mask) == 0) {
            return num | mask;
        }
        mask >>= 1;
    }
    
    return num;
}

int main(void) {
    unsigned int test_values[] = {0, 1, 5, 255, 0x80000000u, 0xFFFFFFFFu};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printf("Input: 0x%08X, Output: 0x%08X\n", 
               test_values[i], 
               set_leftmost_unset_bit(test_values[i]));
    }
    
    return 0;
}