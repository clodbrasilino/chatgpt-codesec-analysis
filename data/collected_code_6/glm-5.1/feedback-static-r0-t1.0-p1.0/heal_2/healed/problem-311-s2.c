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

int main(int argc, char *argv[]) {
    unsigned int num = 18;
    unsigned int result = set_leftmost_unset_bit(num);
    printf("%u\n", result);
    return 0;
}