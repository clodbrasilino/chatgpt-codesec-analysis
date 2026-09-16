#include <stdio.h>
#include <stdint.h>

uint32_t set_odd_bits(uint32_t n) {
    return n | 0xAAAAAAAA;
}

int main(void) {
    uint32_t number = 21;
    uint32_t result = set_odd_bits(number);
    
    printf("Original: %u\n", number);
    printf("Modified: %u\n", result);
    
    return 0;
}