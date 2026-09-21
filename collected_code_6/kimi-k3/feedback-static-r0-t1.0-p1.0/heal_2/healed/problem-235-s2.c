#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

uint32_t set_even_bits(uint32_t num)
{
    return num | 0xAAAAAAAAU;
}

int main(void)
{
    char buffer[64];
    char *endptr;
    unsigned long value;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    errno = 0;
    value = strtoul(buffer, &endptr, 10);

    if (endptr == buffer || errno == ERANGE || value > UINT32_MAX) {
        return 1;
    }

    printf("%" PRIu32 "\n", set_even_bits((uint32_t)value));

    return 0;
}