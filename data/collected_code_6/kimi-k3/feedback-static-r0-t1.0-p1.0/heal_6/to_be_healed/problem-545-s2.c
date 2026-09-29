#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t toggle_first_last_bits(uint32_t num)
{
    return num ^ (1u | (1u << (sizeof(uint32_t) * 8 - 1)));
}

int main(void)
{
    uint32_t num;
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu32, &num) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    uint32_t result = toggle_first_last_bits(num);
    printf("%" PRIu32 "\n", result);
    
    return 0;
}