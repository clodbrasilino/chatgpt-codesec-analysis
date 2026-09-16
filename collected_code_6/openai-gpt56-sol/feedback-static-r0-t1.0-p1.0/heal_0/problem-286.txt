#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int64_t max_contiguous_sum_repeated(const int64_t *array, size_t length, uint64_t repetitions)
{
    int64_t total = 0;
    int64_t prefix = 0;
    int64_t max_prefix = array[0];
    int64_t suffix = 0;
    int64_t max_suffix = array[length - 1];
    int64_t current = array[0];
    int64_t best = array[0];

    for (size_t i = 0; i < length; ++i) {
        total += array[i];
        prefix += array[i];

        if (prefix > max_prefix) {
            max_prefix = prefix;
        }

        if (i > 0) {
            current = current > 0 ? current + array[i] : array[i];
            if (current > best) {
                best = current;
            }
        }

        suffix += array[length - 1 - i];
        if (suffix > max_suffix) {
            max_suffix = suffix;
        }
    }

    if (repetitions == 1) {
        return best;
    }

    int64_t combined = max_suffix + max_prefix;

    if (total > 0 && repetitions > 2) {
        combined += total * (int64_t)(repetitions - 2);
    }

    return combined > best ? combined : best;
}

int main(void)
{
    size_t length;
    uint64_t repetitions;

    if (scanf("%zu %" SCNu64, &length, &repetitions) != 2 ||
        length == 0 ||
        repetitions == 0 ||
        repetitions > (uint64_t)INT64_MAX) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    int64_t result = max_contiguous_sum_repeated(array, length, repetitions);

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}