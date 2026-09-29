#include <stdio.h>
#include <stdint.h>

uint32_t set_odd_bits(uint32_t num) {
    uint32_t odd_mask = 0xAAAAAAAA;
    return num | odd_mask;
}

int main(void) {
    uint32_t num;
    
    if (scanf("%u", &num) != 1) {
        return 1;
    }
    
    uint32_t result = set_odd_bits(num);
    printf("%u\n", result);
    
    return 0;
}