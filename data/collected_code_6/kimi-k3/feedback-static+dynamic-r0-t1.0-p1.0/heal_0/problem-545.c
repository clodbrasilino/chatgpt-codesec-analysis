#include <stdio.h>
#include <stdint.h>
#include <limits.h>

unsigned int toggle_first_last_bits(unsigned int num)
{
    unsigned int first_bit_mask = 1U;
    unsigned int last_bit_mask = 1U << (sizeof(unsigned int) * CHAR_BIT - 1U);
    
    return num ^ first_bit_mask ^ last_bit_mask;
}

int main(void)
{
    unsigned int num;
    unsigned int result;
    
    if (scanf("%u", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    result = toggle_first_last_bits(num);
    printf("%u\n", result);
    
    return 0;
}