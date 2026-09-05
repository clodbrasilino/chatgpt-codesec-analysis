#include <stdio.h>
#include <stdint.h>
#include <limits.h>

unsigned int set_rightmost_unset_bit(unsigned int n)
{
    if (n == UINT_MAX) {
        return n;
    }
    return n | (n + 1);
}

int main(void)
{
    unsigned int test_values[] = {0, 1, 2, 5, 10, 15, 21, 31};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        unsigned int result = set_rightmost_unset_bit(test_values[i]);
        printf("Input: %u, Output: %u\n", test_values[i], result);
    }

    return 0;
}