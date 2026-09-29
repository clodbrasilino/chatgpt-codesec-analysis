#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

static uint64_t sum_fifth_powers(uint64_t n)
{
    uint64_t sum = 0;
    uint64_t i;

    for (i = 1; i <= n; ++i)
    {
        if (i > UINT64_MAX / i)
        {
            return UINT64_MAX;
        }
        uint64_t square = i * i;

        if (square > UINT64_MAX / square)
        {
            return UINT64_MAX;
        }
        uint64_t fourth = square * square;

        if (fourth > UINT64_MAX / i)
        {
            return UINT64_MAX;
        }
        uint64_t fifth = fourth * i;

        if (sum > UINT64_MAX - fifth)
        {
            return UINT64_MAX;
        }
        sum += fifth;
    }

    return sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    uint64_t n;
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    errno = 0;
    n = strtoull(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0'))
    {
        return 1;
    }

    printf("%" PRIu64 "\n", sum_fifth_powers(n));

    return 0;
}