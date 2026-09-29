#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>

static int sum_fourth_powers_of_odds(uint64_t n, uint64_t *result)
{
    const uint64_t max_n = 37687U;
    uint64_t sum = 0U;

    if (result == NULL || n > max_n) {
        return 0;
    }

    for (uint64_t i = 0U; i < n; ++i) {
        uint64_t odd = (2U * i) + 1U;
        uint64_t square = odd * odd;
        uint64_t fourth_power = square * square;

        if (UINT64_MAX - sum < fourth_power) {
            return 0;
        }

        sum += fourth_power;
    }

    *result = sum;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0') {
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