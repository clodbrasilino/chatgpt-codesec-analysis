#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_factors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (uint64_t factor = 1; factor <= number / factor; ++factor) {
        if (number % factor != 0) {
            continue;
        }

        uint64_t paired_factor = number / factor;

        if (factor % 2 == 0) {
            if (UINT64_MAX - total < factor) {
                return 0;
            }
            total += factor;
        }

        if (paired_factor != factor && paired_factor % 2 == 0) {
            if (UINT64_MAX - total < paired_factor) {
                return 0;
            }
            total += paired_factor;
        }
    }

    *sum = total;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uint64_t number;
    uint64_t sum;
    uintmax_t parsed;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed == 0 || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    number = (uint64_t)parsed;

    if (!sum_even_factors(number, &sum)) {
        fprintf(stderr, "Unable to calculate the sum\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}