#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>

uint32_t toggle_odd_bits(uint32_t num)
{
    return num ^ UINT32_C(0xAAAAAAAA);
}

int main(void)
{
    uint32_t num;
    char buffer[64];
    char *endptr;
    unsigned long value;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    errno = 0;
    value = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || value > UINT32_MAX) {
        return 1;
    }

    num = (uint32_t)value;

    printf("%" PRIu32 "\n", toggle_odd_bits(num));

    return 0;
}