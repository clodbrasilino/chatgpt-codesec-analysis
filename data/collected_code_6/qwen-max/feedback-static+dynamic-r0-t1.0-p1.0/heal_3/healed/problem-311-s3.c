#include <stdio.h>
#include <limits.h>

unsigned int setLeftMostUnsetBit(unsigned int n) {
    unsigned int bit = 1;
    while (bit && (n & bit)) {
        bit <<= 1;
    }
    if (bit > n) {
        n |= bit;
    } else {
        unsigned int maxBit = 1U << (sizeof(n) * CHAR_BIT - 1);
        while (bit < maxBit && (n & bit)) {
            bit <<= 1;
        }
        if (bit == maxBit) {
            return n;
        }
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