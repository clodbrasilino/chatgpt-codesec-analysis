#include <stdio.h>
#include <limits.h>

unsigned int set_leftmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }
    unsigned int mask = ~n;
    int shift = 0;
    while (!(mask & (1u << (sizeof(unsigned int) * CHAR_BIT - 1)))) {
        mask <<= 1;
        shift++;
    }
    return n | mask;
}

int main(void) {
    unsigned int val;
    while (scanf("%u", &val) == 1) {
        printf("%u\n", set_leftmost_unset_bit(val));
    }
    return 0;
}