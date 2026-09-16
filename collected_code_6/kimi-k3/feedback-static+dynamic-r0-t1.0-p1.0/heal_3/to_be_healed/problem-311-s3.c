#include <stdio.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 0 failed: expected 14, got <no output>
  *  test case 1 failed: expected 14, got <no output>
  */

unsigned int set_leftmost_unset_bit(unsigned int num) {
    if (num == UINT_MAX) {
        return num;
    }
    
    unsigned int n = ~num;
    unsigned int mask = n & (~(n - 1));
    
    return num | mask;
}

int main(void) {
    unsigned int test_values[] = {0U, 1U, 5U, 7U, 15U, 2147483647U, 4294967295U};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        unsigned int original = test_values[i];
        unsigned int result = set_leftmost_unset_bit(original);
        printf("Original: %u, Result: %u\n", original, result);
    }
    
    return 0;
}