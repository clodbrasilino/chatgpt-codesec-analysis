#include <stdio.h>
#include <limits.h>

unsigned int set_rightmost_unset_bit(unsigned int n) {
    if (n == UINT_MAX) {
        return n;
    }
    return n | (n + 1);
}

int main(void) {
    unsigned int num = 10;
    unsigned int result = set_rightmost_unset_bit(num);
    printf("%u\n", result);

    result = set_rightmost_unset_bit(UINT_MAX);
    printf("%u\n", result);

    return 0;
}