#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t highest_power_of_two(uint64_t number)
{
    if (number == 0) {
        return 0;
    }

    uint64_t result = UINT64_C(1);

    while (number >>= 1) {
        result <<= 1;
    }

    return result;
}

int main(void)
{
    uintmax_t value;
    char extra;

    errno = 0;

    if (scanf(" %" SCNuMAX " %c", &value, &extra) != 1 ||
        errno == ERANGE ||
        value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", highest_power_of_two((uint64_t)value));
    return EXIT_SUCCESS;
}