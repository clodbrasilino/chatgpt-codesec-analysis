#include <stdio.h>
#include <limits.h>

unsigned int set_rightmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }
    return n | (~n);
}

int main(void) {
    printf("%u\n", set_rightmost_unset_bit(10));
    printf("%u\n", set_rightmost_unset_bit(15));
    printf("%u\n", set_rightmost_unset_bit(0));
    printf("%u\n", set_rightmost_unset_bit(UINT_MAX));
    return 0;
}