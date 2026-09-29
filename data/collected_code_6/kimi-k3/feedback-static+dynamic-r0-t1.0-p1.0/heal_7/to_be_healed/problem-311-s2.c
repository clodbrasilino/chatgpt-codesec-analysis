#include <stdio.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 2147483660
  *  test case 0 failed: expected 14, got 2147483658
  *  test case 2 failed: expected 15, got 2147483663
  */

unsigned int set_leftmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }
    
    unsigned int mask = 1;
    unsigned int leftmost_unset = 0;
    
    while (mask != 0) {
        if ((n & mask) == 0) {
            leftmost_unset = mask;
        }
        mask <<= 1;
    }
    
    if (leftmost_unset == 0) {
        return n | 1;
    }
    
    return n | leftmost_unset;
}

int main(void) {
    unsigned int test_cases[] = {0, 1, 5, 10, 15, 16, 31, 32, 63, 64, 127, 128, UINT_MAX};
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        unsigned int original = test_cases[i];
        unsigned int result = set_leftmost_unset_bit(original);
        printf("%u\n", result);
    }
    
    return 0;
}