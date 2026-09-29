#include <stdio.h>

unsigned int toggleBits(unsigned int num) {
    unsigned int mask = ~0;
    mask ^= (1 << 0);
    mask ^= (1 << ((sizeof(num) * 8) - 1));
    return num ^ mask;
}

int main() {
    unsigned int num = 123;
    printf("Original number: %u\n", num);
    printf("Number after toggling bits: %u\n", toggleBits(num));
    return 0;
}