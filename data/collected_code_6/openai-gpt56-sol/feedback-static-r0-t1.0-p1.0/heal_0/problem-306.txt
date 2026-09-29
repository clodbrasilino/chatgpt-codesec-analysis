#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int max_sum_increasing_subsequence(
    const int *values,
    size_t length,
    size_t prefix_end,
    size_t k,
    int64_t *result
) {
    if (values == NULL || result == NULL || length == 0 ||
        prefix_end >= length || k >= length || k <= prefix_end) {
        return -1;
    }

    int64_t *sums = malloc((prefix_end + 1) * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    int found = 0;
    int64_t best = 0;

    for (size_t current = 0; current <= prefix_end; ++current) {
        sums[current] = values[current];

        for (size_t previous = 0; previous < current; ++previous) {
            if (values[previous] < values[current] &&
                sums[previous] + (int64_t)values[current] > sums[current]) {
                sums[current] = sums[previous] + (int64_t)values[current];
            }
        }

        if (values[current] < values[k]) {
            int64_t candidate = sums[current] + (int64_t)values[k];
            if (!found || candidate > best) {
                best = candidate;
                found = 1;
            }
        }
    }

    free(sums);

    if (!found) {
        return 1;
    }

    *result = best;
    return 0;
}

int main(void) {
    size_t length;
    size_t prefix_end;
    size_t k;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = malloc(length * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < length; ++index) {
        if (scanf("%d", &values[index]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%zu %zu", &prefix_end, &k) != 2) {
        free(values);
        return EXIT_FAILURE;
    }

    int64_t result;
    int status = max_sum_increasing_subsequence(
        values,
        length,
        prefix_end,
        k,
        &result
    );

    free(values);

    if (status != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}