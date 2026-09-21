#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[5];
    uint64_t value = 1;
    size_t i;

    if (result == NULL || n == 0 || n > 4934) {
        return 0;
    }

    factors[0] = n;
    factors[1] = n + 1;
    factors[2] = 2 * n + 1;
    factors[3] = 3 * n * n + 3 * n - 1;
    factors[4] = 30;

    for (i = 0; i < 4 && factors[4] > 1; ++i) {
        uint64_t divisor = factors[4];
        uint64_t candidate;

        for (candidate = 2; candidate <= divisor; ++candidate) {
            while (divisor % candidate == 0 &&
                   factors[i] % candidate == 0) {
                factors[i] /= candidate;
                divisor /= candidate;
            }
        }

        factors[4] = divisor;
    }

    if (factors[4] != 1) {
        return 0;
    }

    for (i = 0; i < 4; ++i) {
        if (factors[i] != 0 && value > UINT64_MAX / factors[i]) {
            return 0;
        }
        value *= factors[i];
    }

    *result = value;
    return 1;
}

int main(void)
{
    char input[128];
    char extra;
    uint64_t n;
    uint64_t result;

    if (printf("Enter n: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (sscanf(input, " %" SCNu64 " %c", &n, &extra) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n == 0 || n > 4934 || !sum_fourth_powers(n, &result)) {
        fprintf(stderr, "Input is out of the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}