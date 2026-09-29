#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t set_odd_bits(uint64_t value)
{
    return value | UINT64_C(0xAAAAAAAAAAAAAAAA);
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    value = strtoumax(input, &end, 0);

    if (end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return EXIT_FAILURE;
    }

    if (value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", set_odd_bits((uint64_t)value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}