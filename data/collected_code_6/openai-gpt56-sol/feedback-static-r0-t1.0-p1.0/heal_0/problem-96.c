#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_divisors(uint64_t number)
{
    uint64_t count = 1U;

    for (uint64_t divisor = 2U; divisor <= number / divisor; ++divisor) {
        uint64_t exponent = 0U;

        while (number % divisor == 0U) {
            number /= divisor;
            ++exponent;
        }

        count *= exponent + 1U;
    }

    if (number > 1U) {
        count *= 2U;
    }

    return count;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input == 0U || input > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count_divisors((uint64_t)input));
    return EXIT_SUCCESS;
}