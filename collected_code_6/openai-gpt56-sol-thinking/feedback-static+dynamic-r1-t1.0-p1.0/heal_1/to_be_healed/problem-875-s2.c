#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static uint64_t absolute_difference(int64_t first, int64_t second)
{
    return first >= second
        ? (uint64_t)first - (uint64_t)second
        : (uint64_t)second - (uint64_t)first;
}

static bool find_minimum_tuple_difference(
    const Tuple *tuples,
    size_t count,
    uint64_t *minimum_difference)
{
    if (tuples == NULL || count == 0 || minimum_difference == NULL) {
        return false;
    }

    uint64_t minimum = UINT64_MAX;

    for (size_t i = 0; i < count; ++i) {
        uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < minimum) {
            minimum = difference;
        }
    }

    *minimum_difference = minimum;
    return true;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    Tuple *tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64 " %" SCNd64,
                  &tuples[i].first, &tuples[i].second) != 2) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    uint64_t minimum_difference;

    if (!find_minimum_tuple_difference(
            tuples, count, &minimum_difference)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);

    if (printf("%" PRIu64 "\n", minimum_difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}