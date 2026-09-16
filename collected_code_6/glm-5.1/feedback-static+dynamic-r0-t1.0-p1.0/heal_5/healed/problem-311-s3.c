#include <stdio.h>
#include <limits.h>

unsigned int set_leftmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }

    unsigned int mask = 1U;

    while (n & mask) {
        mask <<= 1;
    }

    return n | mask;
}

int main(void) {
    unsigned int val1 = 14;
    unsigned int val2 = 14;
    unsigned int val3 = 15;
    unsigned int val4 = 12;

    printf("%u\n", set_leftmost_unset_bit(val1));
    printf("%u\n", set_leftmost_unset_bit(val2));
    printf("%u\n", set_leftmost_unset_bit(val3));
    printf("%u\n", set_leftmost_unset_bit(val4));

    return 0;
}