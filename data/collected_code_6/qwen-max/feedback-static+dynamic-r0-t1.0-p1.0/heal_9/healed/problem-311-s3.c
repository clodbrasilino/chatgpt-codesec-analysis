#include <stdio.h>
#include <limits.h>

unsigned int setLeftMostUnsetBit(unsigned int n) {
    unsigned int bit = 1;
    while (bit <= (1U << (sizeof(unsigned int) * CHAR_BIT - 2)) && (n & bit)) {
        bit <<= 1;
    }
    if (bit <= (1U << (sizeof(unsigned int) * CHAR_BIT - 1))) {
        n |= bit;
    }
    return n;
}

int main() {
    unsigned int num1 = 0b1011;
    printf("Original number: %u (in binary: %08b)\n", num1, num1);
    num1 = setLeftMostUnsetBit(num1);
    printf("After setting left most unset bit: %u (in binary: %08b)\n", num1, num1);

    unsigned int num2 = 0b10011;
    printf("Original number: %u (in binary: %08b)\n", num2, num2);
    num2 = setLeftMostUnsetBit(num2);
    printf("After setting left most unset bit: %u (in binary: %08b)\n", num2, num2);

    unsigned int num3 = 0b100011;
    printf("Original number: %u (in binary: %08b)\n", num3, num3);
    num3 = setLeftMostUnsetBit(num3);
    printf("After setting left most unset bit: %u (in binary: %08b)\n", num3, num3);

    return 0;
}