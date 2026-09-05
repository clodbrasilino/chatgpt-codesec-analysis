#include <stdio.h>
#include <limits.h>

unsigned int set_rightmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }
    return n | (n + 1);
}

int main(void) {
    unsigned int val1 = 10;
    unsigned int val2 = 15;
    unsigned int val3 = 0;
    unsigned int val4 = UINT_MAX;

    printf("%u\n", set_rightmost_unset_bit(val1));
    printf("%u\n", set_rightmost_unset_bit(val2));
    printf("%u\n", set_rightmost_unset_bit(val3));
    printf("%u\n", set_rightmost_unset_bit(val4));

    return 0;
}