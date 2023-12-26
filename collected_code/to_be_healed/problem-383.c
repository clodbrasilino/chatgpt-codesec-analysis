#include<stdio.h>

unsigned int toggleOddBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA; // Mask with odd bits set
    return num ^ mask; // XOR with mask toggles the odd bits
}

int main() {
    unsigned int num;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num' is initialized [premium-bughuntingUninit]
     */
    scanf("%u", &num);
    printf("Number with toggled odd bits: %u\n", toggleOddBits(num));
    return 0;
}
