#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int rightmost_set_bit_position(uint32_t value)
{
    unsigned int position = 1U;

    if (value == UINT32_C(0)) {
        return 0U;
    }

    while ((value & UINT32_C(1)) == UINT32_C(0)) {
        value >>= 1U;
        ++position;
    }

    return position;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed_value;
    uint32_t value;
    unsigned int position;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned-32-bit-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Invalid unsigned integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(argv[1], &end, 0);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed_value > UINT32_MAX) {
        fprintf(stderr, "Invalid unsigned 32-bit integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    value = (uint32_t)parsed_value;
    position = rightmost_set_bit_position(value);

    printf("%u\n", position);
    return EXIT_SUCCESS;
}