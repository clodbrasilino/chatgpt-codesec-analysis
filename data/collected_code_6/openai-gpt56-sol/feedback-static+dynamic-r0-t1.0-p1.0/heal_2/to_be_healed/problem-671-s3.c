#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 31
  */

static uint32_t set_rightmost_unset_bit(uint32_t value)
{
    return value | (value + UINT32_C(1));
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    uintmax_t input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned-32-bit-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Invalid 32-bit unsigned integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 0);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || input > UINT32_MAX) {
        fprintf(stderr, "Invalid 32-bit unsigned integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", set_rightmost_unset_bit((uint32_t)input));
    return EXIT_SUCCESS;
}