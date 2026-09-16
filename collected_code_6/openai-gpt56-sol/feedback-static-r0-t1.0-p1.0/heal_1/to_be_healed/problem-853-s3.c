#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_factors(uint64_t number, uint64_t *sum)
{
    uint64_t odd_part = number;
    /* Possible weaknesses found:
     *  The scope of the variable 'factor' can be reduced. [variableScope]
     */
    uint64_t factor = 3U;
    uint64_t result = 1U;

    if (number == 0U || sum == NULL) {
        return 0;
    }

    while ((odd_part % 2U) == 0U) {
        odd_part /= 2U;
    }

    if (odd_part > 1U) {
        uint64_t term = 1U;
        uint64_t power = 1U;

        while ((odd_part % factor) == 0U) {
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

        while (factor <= odd_part / factor) {
            factor += 2U;
            term = 1U;
            power = 1U;

            while ((odd_part % factor) == 0U) {
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

        if (odd_part > 1U) {
            if (odd_part == UINT64_MAX || result > UINT64_MAX / (odd_part + 1U)) {
                return 0;
            }
            result *= odd_part + 1U;
        }
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

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed_number == 0U ||
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