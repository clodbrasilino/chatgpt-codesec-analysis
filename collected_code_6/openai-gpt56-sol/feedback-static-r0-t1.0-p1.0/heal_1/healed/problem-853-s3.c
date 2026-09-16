#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_factors(uint64_t number, uint64_t *sum)
{
    uint64_t odd_part;
    uint64_t result = UINT64_C(1);

    if (number == UINT64_C(0) || sum == NULL) {
        return 0;
    }

    odd_part = number;

    while ((odd_part % UINT64_C(2)) == UINT64_C(0)) {
        odd_part /= UINT64_C(2);
    }

    for (uint64_t factor = UINT64_C(3);
         factor <= odd_part / factor;
         factor += UINT64_C(2)) {
        uint64_t term = UINT64_C(1);
        uint64_t power = UINT64_C(1);

        while ((odd_part % factor) == UINT64_C(0)) {
            odd_part /= factor;

            if (power > UINT64_MAX / factor) {
                return 0;
            }
            power *= factor;

            if (term > UINT64_MAX - power) {
                return 0;
            }
            term += power;
        }

        if (result > UINT64_MAX / term) {
            return 0;
        }
        result *= term;
    }

    if (odd_part > UINT64_C(1)) {
        if (odd_part == UINT64_MAX) {
            return 0;
        }

        if (result > UINT64_MAX / (odd_part + UINT64_C(1))) {
            return 0;
        }
        result *= odd_part + UINT64_C(1);
    }

    *sum = result;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed_number;
    uint64_t sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_number = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        parsed_number == UINTMAX_C(0) ||
        parsed_number > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer.\n");
        return EXIT_FAILURE;
    }

    if (!sum_odd_factors((uint64_t)parsed_number, &sum)) {
        fprintf(stderr, "The sum cannot be represented as uint64_t.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}