#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t set_even_bits(uint64_t value)
{
    return value | UINT64_C(0x5555555555555555);
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 0);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > UINT64_MAX) {
        fprintf(stderr, "Invalid unsigned 64-bit integer\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", set_even_bits((uint64_t)input));
    return EXIT_SUCCESS;
}