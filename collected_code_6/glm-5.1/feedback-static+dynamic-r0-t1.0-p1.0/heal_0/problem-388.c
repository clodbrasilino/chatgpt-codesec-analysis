#include <stdio.h>

unsigned int highest_power_of_2(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n - (n >> 1);
}

int main(void) {
    unsigned int i;
    for (i = 0; i <= 16; ++i) {
        printf("%u -> %u\n", i, highest_power_of_2(i));
    }
    return 0;
}