#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t toggle_even_bits(uint32_t num)
{
    const uint32_t even_bits_mask = 0xAAAAAAAAU;
    return num ^ even_bits_mask;
}

int main(void)
{
    char buffer[32];
    uint32_t number;
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (sscanf(buffer, "%" SCNu32 "%c", &number, &endptr) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("%" PRIu32 "\n", toggle_even_bits(number));
    return 0;
}