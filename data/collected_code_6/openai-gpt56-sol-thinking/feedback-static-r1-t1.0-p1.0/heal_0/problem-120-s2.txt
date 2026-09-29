#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int32_t first;
    int32_t second;
} Tuple;

static bool find_maximum_product(const Tuple *tuples, size_t count, int64_t *result)
{
    if (tuples == NULL || result == NULL || count == 0) {
        return false;
    }

    int64_t maximum = (int64_t)tuples[0].first * tuples[0].second;

    for (size_t i = 1; i < count; ++i) {
        int64_t product = (int64_t)tuples[i].first * tuples[i].second;

        if (product > maximum) {
            maximum = product;
        }
    }

    *result = maximum;
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
        if (scanf("%" SCNd32 " %" SCNd32,
                  &tuples[i].first, &tuples[i].second) != 2) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    int64_t maximum;
    if (!find_maximum_product(tuples, count, &maximum)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}