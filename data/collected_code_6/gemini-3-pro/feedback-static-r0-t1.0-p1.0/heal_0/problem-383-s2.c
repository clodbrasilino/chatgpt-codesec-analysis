#include <stdio.h>
#include <stdint.h>
#include <limits.h>

uint32_t toggle_odd_bits(uint32_t n) {
    uint32_t mask = 0xAAAAAAAA;
    return n ^ mask;
}

int main(void) {
    uint32_t num = 0;
    
    if (scanf("%u", &num) != 1) {
        return 1;
    }
    
    uint32_t result = toggle_odd_bits(num);
    printf("%u\n", result);
    
    return 0;
}