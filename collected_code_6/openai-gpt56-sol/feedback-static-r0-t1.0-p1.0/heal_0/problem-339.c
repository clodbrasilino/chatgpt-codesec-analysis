#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t divisor_occurrences(uint64_t divisor, uint64_t lower, uint64_t upper)
{
    return upper / divisor - (lower - 1U) / divisor;
}

static int find_max_occurring_divisor(uint64_t lower, uint64_t upper,
                                      uint64_t *divisor, uint64_t *occurrences)
{
    if (divisor == NULL || occurrences == NULL ||
        lower == 0U || lower > upper) {
        return -1;
    }

    *divisor = 1U;
    *occurrences = divisor_occurrences(1U, lower, upper);

    for (uint64_t candidate = 2U; candidate <= upper; ++candidate) {
        uint64_t count = divisor_occurrences(candidate, lower, upper);

        if (count > *occurrences) {
            *divisor = candidate;
            *occurrences = count;
        }
    }

    return 0;
}

int main(void)
{
    uint64_t lower;
    uint64_t upper;
    uint64_t divisor;
    uint64_t occurrences;

    if (scanf("%" SCNu64 " %" SCNu64, &lower, &upper) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_max_occurring_divisor(lower, upper,
                                   &divisor, &occurrences) != 0) {
        fputs("Invalid interval\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Divisor: %" PRIu64 "\nOccurrences: %" PRIu64 "\n",
               divisor, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}