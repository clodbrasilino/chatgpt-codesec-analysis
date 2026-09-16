#include <stdio.h>
#include <stdint.h>

uint32_t toggle_even_bits(uint32_t num) {
    return num ^ 0xAAAAAAAA;
}

int main(void) {
    uint32_t num = 23;
    uint32_t result = toggle_even_bits(num);
    
    printf("Original: %u\n", num);
    printf("Toggled: %u\n", result);
    
    return 0;
}