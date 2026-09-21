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
    char buffer[64];
    uint32_t num;
    char *endptr;
    unsigned long value;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
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