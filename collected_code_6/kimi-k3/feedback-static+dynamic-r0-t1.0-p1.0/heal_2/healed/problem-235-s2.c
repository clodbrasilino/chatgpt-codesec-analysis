#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t set_even_bits(uint32_t num)
{
    return num | 0xAAAAAAAAU;
}

int main(void)
{
    uint32_t number;
    
    if (scanf("%" SCNu32, &number) != 1) {
        return 1;
    }
    
    printf("%" PRIu32 "\n", set_even_bits(number));
    
    return 0;
}