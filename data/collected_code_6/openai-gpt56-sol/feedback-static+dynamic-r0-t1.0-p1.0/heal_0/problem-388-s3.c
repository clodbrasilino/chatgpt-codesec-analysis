#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>

static uintmax_t highest_power_of_two(uintmax_t n)
{
    uintmax_t result = 1;

    while (result <= n / 2) {
        result *= 2;
    }

    return result;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-' || n == 0) {
        fprintf(stderr, "Invalid positive integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", highest_power_of_two(n));
    return EXIT_SUCCESS;
}