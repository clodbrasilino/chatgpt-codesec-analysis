#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t rotate_left(uint32_t value, unsigned int count)
{
    const unsigned int width = 32U;
    count %= width;

    return count == 0U ? value : (value << count) | (value >> (width - count));
}

int main(void)
{
    uint32_t value = 0U;
    unsigned int count = 0U;

    if (scanf("%" SCNu32 " %u", &value, &count) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu32 "\n", rotate_left(value, count)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}