#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t toggle_even_bits(uint32_t num)
{
    return num ^ 0xAAAAAAAAU;
}

int main(void)
{
    char buffer[32];
    uint32_t num;
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (sscanf(buffer, "%" SCNu32 "%c", &num, &endptr) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("%" PRIu32 "\n", toggle_even_bits(num));
    
    return 0;
}