#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int max_sum_increasing_subsequence_with_k(
    const int *values,
    size_t length,
    size_t i,
    size_t k,
    int64_t *result)
{
    int64_t *sums = NULL;
    int64_t maximum = 0;
    int found = 0;

    if (values == NULL || result == NULL || length == 0 || i >= length ||
        k >= length || k <= i) {
        return 0;
    }

    sums = malloc((i + 1) * sizeof(*sums));
    if (sums == NULL) {
        return 0;
    }

    for (size_t current = 0; current <= i; ++current) {
        sums[current] = values[current];

        for (size_t previous = 0; previous < current; ++previous) {
            if (values[previous] < values[current] &&
                sums[previous] + (int64_t)values[current] > sums[current]) {
                sums[current] = sums[previous] + (int64_t)values[current];
            }
        }

        if (values[current] < values[k]) {
            int64_t candidate = sums[current] + (int64_t)values[k];

            if (!found || candidate > maximum) {
                maximum = candidate;
                found = 1;
            }
        }
    }

    if (!found) {
        maximum = values[k];
    }

    *result = maximum;
    free(sums);
    return 1;
}

int main(void)
{
    int values[] = {1, 101, 2, 3, 100, 4, 5};
    const size_t length = sizeof(values) / sizeof(values[0]);
    const size_t i = 3;
    const size_t k = 4;
    int64_t result = 0;

    if (!max_sum_increasing_subsequence_with_k(
            values, length, i, k, &result)) {
        fputs("Unable to calculate the maximum sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}