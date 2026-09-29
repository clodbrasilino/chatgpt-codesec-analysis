#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

uint32_t toggle_even_bits(uint32_t num)
{
    const uint32_t even_bits_mask = 0xAAAAAAAAU;
    return num ^ even_bits_mask;
}

int main(void)
{
    char buffer[32];
    uint32_t number;
    char *endptr;
    unsigned long temp;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    temp = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0') || temp > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    number = (uint32_t)temp;
    printf("%" PRIu32 "\n", toggle_even_bits(number));
    return 0;
}