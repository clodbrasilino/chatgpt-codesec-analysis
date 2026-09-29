#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 2147483660
  *  test case 0 failed: expected 14, got 2147483658
  *  test case 2 failed: expected 15, got 2147483663
  */

unsigned int set_leftmost_unset_bit(unsigned int num) {
    unsigned int mask = 1u << (sizeof(unsigned int) * CHAR_BIT - 1);
    while (mask) {
        if (!(num & mask)) {
            return num | mask;
        }
        mask >>= 1;
    }
    return num;
}

int main(void) {
    unsigned int tests[] = {0, 1, 0x7FFFFFFF, 0xFFFFFFFF, 0xAA, 0x80000000};
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < count; ++i) {
        unsigned int input = tests[i];
        unsigned int output = set_leftmost_unset_bit(input);
        printf("Input: 0x%08X -> Output: 0x%08X (%u)\n", input, output, output);
    }

    return 0;
}