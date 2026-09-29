#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int count_set_bits(uintmax_t value)
{
    unsigned int count = 0U;

    while (value != UINTMAX_C(0)) {
        value &= value - UINTMAX_C(1);
        ++count;
    }

    return count;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 0);

    if (errno != 0 || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid nonnegative integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%u\n", count_set_bits(value));
    return EXIT_SUCCESS;
}