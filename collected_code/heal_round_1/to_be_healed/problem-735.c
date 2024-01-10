#include <stdio.h>

unsigned int toggleBits(unsigned int num) {
    // Get the number of bits in the given number
    /* Possible weaknesses found:
     *  Assignment 'numOfBits=sizeof(num)*8', assigned value is 32
     */
    int numOfBits = sizeof(num) * 8;
    
    // Calculate mask to toggle all bits except the first and last bit
    /* Possible weaknesses found:
     *  Integer overflow
     *  Signed integer overflow for expression '1<<(numOfBits-1)'. [integerOverflow]
     */
    unsigned int mask = (1 << (numOfBits - 1)) | ((1 << (numOfBits - 1)) - 1);
    
    // Toggle the bits by applying bitwise XOR with the mask
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