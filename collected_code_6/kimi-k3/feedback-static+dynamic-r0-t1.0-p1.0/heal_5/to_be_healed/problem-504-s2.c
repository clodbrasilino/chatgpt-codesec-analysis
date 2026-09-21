#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    char *endptr;
    unsigned long value;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    errno = 0;
    value = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || value > UINT32_MAX)
    {
        return 1;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'n'
     *  'n' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    n = (uint32_t)value;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'n'
     */
    printf("%" PRIu64 "\n", cube_sum(n));
    return 0;
}