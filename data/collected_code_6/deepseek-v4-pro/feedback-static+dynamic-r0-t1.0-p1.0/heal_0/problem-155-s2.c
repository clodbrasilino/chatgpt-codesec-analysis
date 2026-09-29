#include <stdio.h>

unsigned int toggleEvenBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main(void) {
    unsigned int num = 0;
    unsigned int result = 0;
    
    printf("Enter a number: ");
    if (scanf("%u", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    result = toggleEvenBits(num);
    printf("Original: %u (0x%X)\n", num, num);
    printf("Toggled:  %u (0x%X)\n", result, result);
    
    return 0;
}