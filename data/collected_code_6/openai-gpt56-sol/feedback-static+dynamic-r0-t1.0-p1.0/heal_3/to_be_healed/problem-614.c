#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int cumulative_sum(const Tuple *tuples, size_t count, int64_t *result)
{
    int64_t sum = 0;

    if (result == NULL || (tuples == NULL && count != 0)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (__builtin_add_overflow(sum, tuples[i].first, &sum) ||
            __builtin_add_overflow(sum, tuples[i].second, &sum)) {
            return 0;
        }
    }

    *result = sum;
    return 1;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    Tuple *tuples = NULL;

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64 " %" SCNd64,
                  &tuples[i].first,
                  &tuples[i].second) != 2) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    int64_t sum;

    if (!cumulative_sum(tuples, count, &sum)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}