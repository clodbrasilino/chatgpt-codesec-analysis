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
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu32, &number) != 1) {
        return 1;
    }
    
    printf("%" PRIu32 "\n", set_even_bits(number));
    
    return 0;
}