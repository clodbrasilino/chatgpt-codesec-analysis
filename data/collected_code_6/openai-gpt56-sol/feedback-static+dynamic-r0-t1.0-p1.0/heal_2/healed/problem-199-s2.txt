#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t highest_power_of_two(uint64_t number)
{
    if (number == UINT64_C(0)) {
        return UINT64_C(0);
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

    if (scanf("%" SCNuMAX, &value) != 1 || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int character;

    do {
        character = getchar();
    } while (character != EOF && character != '\n' &&
             (character == ' ' || character == '\t' ||
              character == '\r' || character == '\f' ||
              character == '\v'));

    if (character != EOF && character != '\n') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", highest_power_of_two((uint64_t)value));
    return EXIT_SUCCESS;
}