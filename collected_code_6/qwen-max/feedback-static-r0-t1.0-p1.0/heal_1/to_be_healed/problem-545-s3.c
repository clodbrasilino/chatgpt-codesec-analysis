#include <stdio.h>
#include <stdbool.h>

void toggleFirstLastBits(unsigned int *num) {
    /* Possible weaknesses found:
     *  Signed integer overflow for expression '1<<(sizeof(unsigned int)*8-1)'. [integerOverflow]
     *  Shifting signed 32-bit value by 31 bits is implementation-defined behaviour [shiftTooManyBitsSigned]
     */
    unsigned int mask = 1 | (1 << (sizeof(unsigned int) * 8 - 1));
    *num ^= mask;
}

int main() {
    unsigned int num = 0b10100001; // Example number
    printf("Before: %u\n", num);
    toggleFirstLastBits(&num);
    printf("After: %u\n", num);
    return 0;
}