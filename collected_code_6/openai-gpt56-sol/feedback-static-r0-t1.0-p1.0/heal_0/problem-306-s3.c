#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int max_sum_increasing_with_k(const int *values, size_t length,
                                     size_t i, size_t k, int64_t *result)
{
    if (values == NULL || result == NULL || length == 0 || i >= length ||
        k >= length || k <= i) {
        return -1;
    }

    int64_t *sums = malloc((i + 1) * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    int found = 0;
    int64_t maximum = 0;

    for (size_t current = 0; current <= i; ++current) {
        sums[current] = values[current];

        for (size_t previous = 0; previous < current; ++previous) {
            if (values[previous] < values[current]) {
                int64_t candidate = sums[previous] + values[current];
                if (candidate > sums[current]) {
                    sums[current] = candidate;
                }
            }
        }

        if (values[current] < values[k]) {
            int64_t candidate = sums[current] + values[k];
            if (!found || candidate > maximum) {
                maximum = candidate;
                found = 1;
            }
        }
    }

    free(sums);

    if (!found) {
        return 1;
    }

    *result = maximum;
    return 0;
}

int main(void)
{
    size_t length;
    size_t i;
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

    if (scanf("%zu %zu", &i, &k) != 2) {
        free(values);
        return EXIT_FAILURE;
    }

    int64_t result;
    int status = max_sum_increasing_with_k(values, length, i, k, &result);
    free(values);

    if (status != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}