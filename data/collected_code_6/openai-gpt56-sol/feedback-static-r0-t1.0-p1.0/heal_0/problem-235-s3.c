#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t set_even_bits(uint64_t value)
{
    return value | UINT64_C(0x5555555555555555);
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = strtoumax(argv[1], &end, 0);

    if (end == argv[1] || *end != '\0' || input > UINT64_MAX) {
        fprintf(stderr, "Invalid unsigned 64-bit integer\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", set_even_bits((uint64_t)input));
    return EXIT_SUCCESS;
}