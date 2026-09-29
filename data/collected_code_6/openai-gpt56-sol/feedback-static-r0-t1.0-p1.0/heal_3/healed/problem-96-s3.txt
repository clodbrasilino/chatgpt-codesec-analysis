#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_divisors(uint64_t value)
{
    uint64_t count = 0;

    for (uint64_t divisor = 1; divisor <= value / divisor; ++divisor) {
        if (value % divisor == 0) {
            count += divisor == value / divisor ? UINT64_C(1) : UINT64_C(2);
        }
    }

    return count;
}

int main(void)
{
    uintmax_t value;
    char extra;
    int result;

    result = scanf("%" SCNuMAX " %c", &value, &extra);

    if (result != 1 || value == 0 || value > UINT64_MAX) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count_divisors((uint64_t)value));

    return EXIT_SUCCESS;
}