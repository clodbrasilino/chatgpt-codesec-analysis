#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int count_bits_set(unsigned int num, unsigned int oth, unsigned int nth)
{
    if (oth >= (sizeof(unsigned int) * CHAR_BIT) || 
        nth >= (sizeof(unsigned int) * CHAR_BIT)) {
        return 0;
    }
    
    unsigned int mask = (1U << oth) | (1U << nth);
    return (num & mask) == mask;
}

int main(void)
{
    unsigned int num = 0xFF;
    unsigned int oth = 0;
    unsigned int nth = 7;
    
    int result = count_bits_set(num, oth, nth);
    
    if (result == 1) {
        printf("Bits %u and %u are set in %u\n", oth, nth, num);
    } else {
        printf("Bits %u and %u are not both set in %u\n", oth, nth, num);
    }
    
    return 0;
}