#include <stdio.h>
#include <limits.h>

unsigned int setLeftMostUnsetBit(unsigned int n) {
    unsigned int bit = 1;
    while (bit <= (1U << (sizeof(unsigned int) * CHAR_BIT - 2)) && (n & bit)) {
        bit <<= 1;
    }
    if (bit < (1U << (sizeof(unsigned int) * CHAR_BIT - 1))) {
        n |= bit;
    }
    return n;
}

int main() {
    unsigned int num = 0b101010;
    printf("Original number: %u (in binary: %08b)\n", num, num);
    num = setLeftMostUnsetBit(num);
    printf("After setting left most unset bit: %u (in binary: %08b)\n", num, num);
    return 0;
}