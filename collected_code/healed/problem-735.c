#include <stdio.h>

unsigned int toggleBits(unsigned int num) {
    unsigned int sizeOfUnsignedInt = sizeof(num) * 8;
    unsigned int mask = ((1u << (sizeOfUnsignedInt - 2)) - 1) << 1;

    num ^= mask;

    return num;
}

int main() {
    unsigned int num = 12345;
    unsigned int toggledNum = toggleBits(num);

    printf("Original number: %u\n", num);
    printf("Toggled number: %u\n", toggledNum);

    return 0;
}