#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

bool are_all_bits_unset(unsigned int value, unsigned int start, unsigned int end)
{
    if (start > end || end >= (sizeof(value) * CHAR_BIT))
    {
        return false;
    }
    
    unsigned int mask = 0;
    for (unsigned int i = start; i <= end; i++)
    {
        mask |= (1U << i);
    }
    
    return (value & mask) == 0;
}

int main(void)
{
    unsigned int value = 0b00000000;
    unsigned int start = 0;
    unsigned int end = 3;
    
    if (are_all_bits_unset(value, start, end))
    {
        printf("All bits in range [%u, %u] are unset.\n", start, end);
    }
    else
    {
        printf("Not all bits in range [%u, %u] are unset.\n", start, end);
    }
    
    value = 0b00000101;
    start = 1;
    end = 2;
    
    if (are_all_bits_unset(value, start, end))
    {
        printf("All bits in range [%u, %u] are unset.\n", start, end);
    }
    else
    {
        printf("Not all bits in range [%u, %u] are unset.\n", start, end);
    }
    
    return 0;
}