#include <stdio.h>
#include <stdint.h>

uint32_t set_even_bits(uint32_t num);

uint32_t set_even_bits(uint32_t num) {
    return num | 0x55555555U;
}

int main(void) {
    uint32_t num = 10U;
    uint32_t result = set_even_bits(num);
    
    if (printf("%u\n", result) < 0) {
        return 1;
    }
    
    return 0;
}