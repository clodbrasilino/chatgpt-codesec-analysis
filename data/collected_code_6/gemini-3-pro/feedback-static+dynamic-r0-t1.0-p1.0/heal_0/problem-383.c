#include <stdio.h>
#include <stdint.h>

uint32_t toggle_odd_bits(uint32_t num) {
    uint32_t mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main(void) {
    uint32_t num = 10;
    uint32_t result = toggle_odd_bits(num);
    
    printf("%u\n", result);
    
    return 0;
}