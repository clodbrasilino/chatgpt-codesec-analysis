#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    char buffer[64];
    char *endptr;
    unsigned long value;
    uint32_t n;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len == 0 || len >= sizeof(buffer) - 1)
    {
        return 1;
    }

    if (buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0)
    {
        return 1;
    }

    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit((unsigned char)buffer[i]))
        {
            return 1;
        }
    }

    errno = 0;
    value = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\0' || value > UINT32_MAX)
    {
        return 1;
    }

    n = (uint32_t)value;
    printf("%" PRIu64 "\n", cube_sum(n));
    return 0;
}