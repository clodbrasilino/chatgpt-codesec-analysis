#include <stdio.h>

unsigned int setAllOddBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num | mask;
}

int main(void) {
    unsigned int input = 0;
    unsigned int result = 0;
    
    printf("Enter a number: ");
    if (scanf("%u", &input) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    result = setAllOddBits(input);
    printf("Result after setting all odd bits: %u\n", result);
    printf("Hexadecimal: 0x%08X\n", result);
    
    return 0;
}