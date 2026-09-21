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
    uint32_t number;
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu32, &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("%" PRIu32 "\n", toggle_even_bits(number));
    return 0;
}