#include <stdio.h>
#include <stdlib.h>

unsigned int set_leftmost_unset_bit(unsigned int n) {
    if (~n == 0) {
        return n;
    }
    unsigned int mask = 1U << (sizeof(unsigned int) * 8 - 1);
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