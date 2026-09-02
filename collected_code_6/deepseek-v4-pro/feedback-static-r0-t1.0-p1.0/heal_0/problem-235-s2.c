#include <stdio.h>

unsigned int setEvenBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num | mask;
}

int main(void) {
    unsigned int number;
    
    printf("Enter a number: ");
    if (scanf("%u", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    unsigned int result = setEvenBits(number);
    printf("Original: 0x%X\n", number);
    printf("Result: 0x%X\n", result);
    
    return 0;
}