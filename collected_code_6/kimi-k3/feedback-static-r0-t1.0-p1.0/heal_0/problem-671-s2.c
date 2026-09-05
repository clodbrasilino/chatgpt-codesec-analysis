#include <stdio.h>
#include <stdint.h>
#include <limits.h>

unsigned int set_rightmost_unset_bit(unsigned int value)
{
    if (value == UINT_MAX) {
        return value;
    }
    return value | (value + 1);
}

int main(void)
{
    unsigned int test_values[] = {0, 1, 2, 5, 7, 10, 15, 16, 21, UINT_MAX};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;
    
    for (i = 0; i < num_tests; i++) {
        unsigned int input = test_values[i];
        unsigned int result = set_rightmost_unset_bit(input);
        printf("Input: %u, Result: %u\n", input, result);
    }
    
    return 0;
}