#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t toggle_odd_bits(uintmax_t value)
{
    uintmax_t mask = 0;

    for (size_t bit = 1; bit < sizeof(value) * 8U; bit += 2U) {
        mask |= UINTMAX_C(1) << bit;
    }

    return value ^ mask;
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

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", toggle_odd_bits(value));
    return EXIT_SUCCESS;
}