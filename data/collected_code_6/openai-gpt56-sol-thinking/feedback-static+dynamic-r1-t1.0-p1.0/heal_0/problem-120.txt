#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int32_t first;
    int32_t second;
} Tuple;

bool find_maximum_product(const Tuple *tuples, size_t count, int64_t *maximum)
{
    if (tuples == NULL || maximum == NULL || count == 0) {
        return false;
    }

    *maximum = (int64_t)tuples[0].first * tuples[0].second;

    for (size_t i = 1; i < count; ++i) {
        int64_t product = (int64_t)tuples[i].first * tuples[i].second;

        if (product > *maximum) {
            *maximum = product;
        }
    }

    return true;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    int64_t maximum;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%" SCNd32 " %" SCNd32,
                  &tuples[i].first, &tuples[i].second) != 2) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_maximum_product(tuples, count, &maximum)) {
        fputs("Unable to find maximum product\n", stderr);
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