#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>

static int sum_fourth_powers_of_odds(uint64_t n, uint64_t *result)
{
    const uint64_t max_n = UINT64_C(37687);
    uint64_t sum = UINT64_C(0);

    if (result == NULL || n > max_n) {
        return 0;
    }

    for (uint64_t i = UINT64_C(0); i < n; ++i) {
        const uint64_t odd = (UINT64_C(2) * i) + UINT64_C(1);
        const uint64_t square = odd * odd;
        const uint64_t fourth_power = square * square;

        if (UINT64_MAX - sum < fourth_power) {
            return 0;
        }

        sum += fourth_power;
    }

    *result = sum;
    return 1;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (input > UINT64_MAX ||
        !sum_fourth_powers_of_odds((uint64_t)input, &result)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}