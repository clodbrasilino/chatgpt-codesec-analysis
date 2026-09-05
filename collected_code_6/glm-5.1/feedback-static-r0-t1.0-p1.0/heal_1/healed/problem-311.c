#include <stdio.h>
#include <limits.h>

unsigned int set_leftmost_unset_bit(unsigned int n) {
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
    unsigned int val = 0;
    if (scanf("%u", &val) == 1) {
        printf("%u\n", set_leftmost_unset_bit(val));
    }
    return 0;
}