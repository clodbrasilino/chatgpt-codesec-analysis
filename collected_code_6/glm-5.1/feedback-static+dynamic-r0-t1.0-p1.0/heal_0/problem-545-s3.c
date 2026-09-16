#include <stdio.h>
#include <limits.h>

unsigned int toggle_first_last(unsigned int num) {
    unsigned int mask = 0;
    mask |= 1u << 0;
    mask |= 1u << (sizeof(num) * CHAR_BIT - 1);
    return num ^ mask;
}

int main(void) {
    unsigned int val = 0;
    unsigned int res = toggle_first_last(val);
    printf("%u\n", res);
    return 0;
}