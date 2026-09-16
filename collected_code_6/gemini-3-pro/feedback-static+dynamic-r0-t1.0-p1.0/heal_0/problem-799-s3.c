#include <stdio.h>
#include <stdint.h>

uint32_t left_rotate(uint32_t number, uint32_t shift) {
    if (shift == 0) {
        return number;
    }
    
    shift = shift % 32;
    return (number << shift) | (number >> (32 - shift));
}

int main(void) {
    uint32_t number = 0x12345678;
    uint32_t shift = 8;
    uint32_t result = left_rotate(number, shift);
    
    printf("Original: 0x%08X\n", number);
    printf("Shifted:  0x%08X\n", result);
    
    return 0;
}