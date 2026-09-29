#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t cube_sum(uint32_t n)
{
    uint64_t sum = 0;
    for (uint32_t i = 1; i <= n; i++)
    {
        sum += (uint64_t)i * i * i;
    }
    return sum;
}

int main(void)
{
    uint32_t n;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu32, &n) != 1)
    {
        return 1;
    }
    printf("%" PRIu64 "\n", cube_sum(n));
    return 0;
}