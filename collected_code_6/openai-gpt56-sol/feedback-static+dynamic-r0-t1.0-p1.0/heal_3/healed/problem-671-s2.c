#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_rightmost_unset_bit(uint32_t value)
{
    uint32_t unset_bits = ~value;

    if (unset_bits == 0) {
        return value;
    }

    return value | (unset_bits & (uint32_t)(0U - unset_bits));
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint32_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned-32-bit-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Invalid 32-bit unsigned integer\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 0);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input > UINT32_MAX) {
        fprintf(stderr, "Invalid 32-bit unsigned integer\n");
        return EXIT_FAILURE;
    }

    result = set_rightmost_unset_bit((uint32_t)input);
    printf("%" PRIu32 "\n", result);

    return EXIT_SUCCESS;
}