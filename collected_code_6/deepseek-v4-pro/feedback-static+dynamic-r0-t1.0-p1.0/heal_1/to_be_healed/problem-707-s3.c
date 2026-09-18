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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:543,execs:293,op:havoc,rep:1; likely memory-safety defect
  */

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