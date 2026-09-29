#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t sum_fifth_powers(uint64_t n)
{
    uint64_t sum = 0;
    uint64_t i;

    for (i = 1; i <= n; ++i)
    {
        uint64_t square = i * i;
        uint64_t fifth = square * square * i;
        sum += fifth;
    }

    return sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    uint64_t n;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(buffer, "%" SCNu64, &n) != 1)
    {
        return 1;
    }

    printf("%" PRIu64 "\n", sum_fifth_powers(n));

    return 0;
}