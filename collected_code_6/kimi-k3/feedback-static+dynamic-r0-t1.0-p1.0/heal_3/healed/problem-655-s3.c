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
    char buffer[32];
    uint64_t n;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    if (sscanf(buffer, "%" SCNu64, &n) != 1)
    {
        return 1;
    }

    printf("%" PRIu64 "\n", sum_fifth_powers(n));

    return 0;
}