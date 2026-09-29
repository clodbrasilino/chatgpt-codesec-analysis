#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    else if (len == sizeof(buffer) - 1 && !feof(stdin))
    {
        return 1;
    }

    errno = 0;
    n = strtoull(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer || *endptr != '\0')
    {
        return 1;
    }

    printf("%" PRIu64 "\n", sum_fifth_powers(n));

    return 0;
}