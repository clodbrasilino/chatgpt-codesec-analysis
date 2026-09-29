#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

static bool checked_mul_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (a != 0 && b > UINT64_MAX / a)
    {
        return false;
    }
    *result = a * b;
    return true;
}

static bool checked_add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (b > UINT64_MAX - a)
    {
        return false;
    }
    *result = a + b;
    return true;
}

static bool sum_fifth_powers(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;
    uint64_t i;

    for (i = 1; i <= n; ++i)
    {
        uint64_t square, fourth, fifth;

        if (!checked_mul_u64(i, i, &square))
        {
            return false;
        }
        if (!checked_mul_u64(square, square, &fourth))
        {
            return false;
        }
        if (!checked_mul_u64(fourth, i, &fifth))
        {
            return false;
        }
        if (!checked_add_u64(sum, fifth, &sum))
        {
            return false;
        }
    }

    *result = sum;
    return true;
}

int main(void)
{
    uint64_t n;
    uint64_t result;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin))
    {
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    errno = 0;
    n = strtoull(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\0')
    {
        return 1;
    }

    if (!sum_fifth_powers(n, &result))
    {
        return 1;
    }

    printf("%" PRIu64 "\n", result);

    return 0;
}