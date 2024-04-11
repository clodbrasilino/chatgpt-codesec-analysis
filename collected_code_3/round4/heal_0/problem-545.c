#include <stdio.h>

unsigned int toggleBits(unsigned int num) {
    unsigned int mask = 1 << (sizeof(num) * 8 - 1);
    mask |= 1;
    return num ^ mask;
}

int main() {
    unsigned int num = 15;
    printf("Original number: %u\n", num);
    num = toggleBits(num);
    printf("Number after toggling first and last bits: %u\n", num);
    return 0;
}