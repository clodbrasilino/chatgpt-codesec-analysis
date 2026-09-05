#include <stdio.h>
#include <limits.h>

unsigned int set_leftmost_unset_bit(unsigned int n) {
    if (n == 0) {
        return 1;
    }

    if (n == UINT_MAX) {
        return n;
    }

    unsigned int mask = 1U << (sizeof(unsigned int) * CHAR_BIT - 1);
    
    while (n & mask) {
        mask >>= 1;
    }
    
    return n | mask;
}

int main(void) {
    unsigned int val1 = 0;
    unsigned int val2 = UINT_MAX;
    unsigned int val3 = 5;
    unsigned int val4 = 12;

    printf("%u\n", set_leftmost_unset_bit(val1));
    printf("%u\n", set_leftmost_unset_bit(val2));
    printf("%u\n", set_leftmost_unset_bit(val3));
    printf("%u\n", set_leftmost_unset_bit(val4));

    return 0;
}