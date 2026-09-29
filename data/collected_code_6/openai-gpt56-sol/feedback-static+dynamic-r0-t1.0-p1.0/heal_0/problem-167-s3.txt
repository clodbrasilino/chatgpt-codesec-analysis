#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int smallest_power_of_two(uintmax_t n, uintmax_t *result)
{
    uintmax_t power = 1;

    if (result == NULL || n == 0) {
        return -1;
    }

    while (power < n) {
        if (power > UINTMAX_MAX / 2) {
            return -1;
        }
        power *= 2;
    }

    *result = power;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t n;
    uintmax_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-' || n == 0) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    if (smallest_power_of_two(n, &result) != 0) {
        fprintf(stderr, "No representable power of two is greater than or equal to %" PRIuMAX "\n", n);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", result);
    return EXIT_SUCCESS;
}