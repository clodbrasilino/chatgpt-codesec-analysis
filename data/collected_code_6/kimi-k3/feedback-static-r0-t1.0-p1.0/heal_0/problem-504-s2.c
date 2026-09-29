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
    if (scanf("%" SCNu32, &n) != 1)
    {
        return 1;
    }
    printf("%" PRIu64 "\n", cube_sum(n));
    return 0;
}