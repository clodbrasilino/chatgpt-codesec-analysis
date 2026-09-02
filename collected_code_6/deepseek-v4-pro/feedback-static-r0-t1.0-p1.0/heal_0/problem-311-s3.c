#include <stdio.h>

unsigned int set_leftmost_unset_bit(unsigned int num) {
    unsigned int mask = 1u << 31;
    while (mask) {
        if (!(num & mask)) {
            return num | mask;
        }
        mask >>= 1;
    }
    return num;
}

int main(void) {
    unsigned int tests[] = {0, 1, 0x7FFFFFFF, 0xFFFFFFFF, 0b10101010, 0x80000000};
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < count; ++i) {
        unsigned int input = tests[i];
        unsigned int output = set_leftmost_unset_bit(input);
        printf("Input: 0x%08X -> Output: 0x%08X\n", input, output);
    }

    return 0;
}