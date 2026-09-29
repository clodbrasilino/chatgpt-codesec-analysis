#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long set_rightmost_unset_bit(unsigned long long value)
{
    unsigned long long bit = 1ULL;

    while ((value & bit) != 0ULL) {
        bit <<= 1;
    }

    return value | bit;
}

int main(int argc, char *argv[])
{
    char *end;
    unsigned long long value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Invalid unsigned integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoull(argv[1], &end, 0);

    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        fprintf(stderr, "Invalid unsigned integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (value == ULLONG_MAX) {
        fprintf(stderr, "All bits are already set.\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", set_rightmost_unset_bit(value));

    return EXIT_SUCCESS;
}