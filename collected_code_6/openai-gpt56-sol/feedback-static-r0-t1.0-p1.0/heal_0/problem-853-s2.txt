#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_factors(uint64_t number, uint64_t *sum)
{
    uint64_t factor;
    uint64_t result = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (factor = 1; factor <= number / factor; factor += 2) {
        uint64_t paired_factor;

        if (number % factor != 0) {
            continue;
        }

        paired_factor = number / factor;

        if (UINT64_MAX - result < factor) {
            return 0;
        }
        result += factor;

        if (paired_factor != factor && (paired_factor & 1U) != 0U) {
            if (UINT64_MAX - result < paired_factor) {
                return 0;
            }
            result += paired_factor;
        }
    }

    *sum = result;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed == 0 || parsed > UINT64_MAX) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_factors((uint64_t)parsed, &sum)) {
        fputs("Unable to calculate the sum without overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}