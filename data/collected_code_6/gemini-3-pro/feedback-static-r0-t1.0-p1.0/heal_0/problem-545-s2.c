#include <stdio.h>
#include <limits.h>

unsigned int toggleFirstAndLastBits(unsigned int num) {
    unsigned int numBits = sizeof(num) * CHAR_BIT;
    
    if (numBits <= 1) {
        return num ^ 1;
    }
    
    unsigned int firstBitMask = 1U << (numBits - 1);
    unsigned int lastBitMask = 1U;
    
    return num ^ (firstBitMask | lastBitMask);
}

int main(void) {
    unsigned int num = 0x0F0F0F0F;
    unsigned int result;
    
    result = toggleFirstAndLastBits(num);
    
    printf("Original: 0x%08X\n", num);
    printf("Toggled:  0x%08X\n", result);
    
    return 0;
}