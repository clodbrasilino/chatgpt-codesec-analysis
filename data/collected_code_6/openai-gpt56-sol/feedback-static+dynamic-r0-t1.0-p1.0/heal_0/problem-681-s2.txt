#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t smallest_prime_divisor(uint64_t number)
{
    if (number < 2U) {
        return 0U;
    }

    if (number % 2U == 0U) {
        return 2U;
    }

    for (uint64_t divisor = 3U; divisor <= number / divisor; divisor += 2U) {
        if (number % divisor == 0U) {
            return divisor;
        }
    }

    return number;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer greater than or equal to 2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || value < 2U || value > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", smallest_prime_divisor((uint64_t)value));
    return EXIT_SUCCESS;
}