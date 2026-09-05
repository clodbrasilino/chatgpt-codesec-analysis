#include <stdio.h>
#include <stdint.h>
#include <limits.h>

unsigned int set_leftmost_unset_bit(unsigned int num) {
    if (num == UINT_MAX) {
        return num;
    }
    
    unsigned int mask = 1U << (sizeof(unsigned int) * CHAR_BIT - 1);
    
    while (mask != 0 && (num & mask) != 0) {
        mask >>= 1;
    }
    
    if (mask != 0) {
        num |= mask;
    }
    
    return num;
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