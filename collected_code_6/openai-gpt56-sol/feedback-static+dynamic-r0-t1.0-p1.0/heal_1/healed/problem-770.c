#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers_of_odds(uint64_t n, uint64_t *result)
{
    __uint128_t sum = 0;

    if (result == NULL || n > UINT64_C(3884)) {
        return -1;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        const __uint128_t odd = (__uint128_t)2 * i - 1;
        sum += odd * odd * odd * odd;
    }

    if (sum > UINT64_MAX) {
        return -1;
    }

    *result = (uint64_t)sum;
    return 0;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (sum_fourth_powers_of_odds((uint64_t)input, &result) != 0) {
        fprintf(stderr, "Result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}