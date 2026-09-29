#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

uint32_t toggle_first_last_bits(uint32_t num)
{
    return num ^ (1u | (1u << (sizeof(uint32_t) * CHAR_BIT - 1)));
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    uint32_t num;
    char *endptr;
    unsigned long value;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    len = 0;
    while (len < sizeof(buffer) && buffer[len] != '\0')
    {
        len++;
    }

    if (len == sizeof(buffer))
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin))
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    value = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0') || value > UINT32_MAX)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    num = (uint32_t)value;
    uint32_t result = toggle_first_last_bits(num);
    printf("%" PRIu32 "\n", result);

    return 0;
}