#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t toggle_even_bits(uint32_t num)
{
    return num ^ 0xAAAAAAAAU;
}

int main(void)
{
    uint32_t num;
    
    if (scanf("%" SCNu32, &num) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("%" PRIu32 "\n", toggle_even_bits(num));
    
    return 0;
}