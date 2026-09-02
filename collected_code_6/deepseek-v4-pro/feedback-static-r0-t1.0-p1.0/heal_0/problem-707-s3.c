#include <stdio.h>

unsigned int countSetBitsFrom1ToN(unsigned int n) {
    unsigned int totalSetBits = 0;
    unsigned int i = 0;
    unsigned int bitPosition = 1;
    
    while (bitPosition <= n) {
        unsigned int totalPairs = (n + 1) / (bitPosition * 2);
        unsigned int remainder = (n + 1) % (bitPosition * 2);
        
        totalSetBits += totalPairs * bitPosition;
        
        if (remainder > bitPosition) {
            totalSetBits += remainder - bitPosition;
        }
        
        bitPosition <<= 1;
        i++;
    }
    
    return totalSetBits;
}

int main(void) {
    unsigned int n;
    
    printf("Enter a positive integer: ");
    if (scanf("%u", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n == 0) {
        printf("Total set bits from 1 to 0: 0\n");
        return 0;
    }
    
    unsigned int result = countSetBitsFrom1ToN(n);
    printf("Total set bits from 1 to %u: %u\n", n, result);
    
    return 0;
}