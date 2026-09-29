#include <stdio.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 1 failed: expected 15, got <no output>
  *  test case 0 failed: expected 23, got <no output>
  */

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
        printf("%u\n", result);
    }

    return 0;
}