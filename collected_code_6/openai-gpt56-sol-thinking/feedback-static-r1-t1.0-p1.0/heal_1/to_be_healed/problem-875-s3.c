#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    return a >= b ? (uint64_t)a - (uint64_t)b
                  : (uint64_t)b - (uint64_t)a;
}

static int find_minimum_pair_difference(const Tuple *tuples, size_t count,
                                        uint64_t *minimum)
{
    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    *minimum = absolute_difference(tuples[0].first, tuples[0].second);

    for (size_t i = 1; i < count; ++i) {
        uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < *minimum) {
            *minimum = difference;
        }
    }

    return 1;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    uint64_t minimum;

    if (scanf("%zu", &count) != 1 || count == 0) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64 " %" SCNd64,
                  &tuples[i].first, &tuples[i].second) != 2) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_minimum_pair_difference(tuples, count, &minimum)) {
        fputs("Unable to calculate minimum difference\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", minimum);
    free(tuples);

    return EXIT_SUCCESS;
}