#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t largest_prime_factor(uint64_t number)
{
    uint64_t largest = 0;

    while (number % 2U == 0U) {
        largest = 2U;
        number /= 2U;
    }

    for (uint64_t factor = 3U; factor <= number / factor; factor += 2U) {
        while (number % factor == 0U) {
            largest = factor;
            number /= factor;
        }
    }

    if (number > 1U) {
        largest = number;
    }

    return largest;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer greater than 1>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        value < 2U || value > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", largest_prime_factor((uint64_t)value));
    return EXIT_SUCCESS;
}