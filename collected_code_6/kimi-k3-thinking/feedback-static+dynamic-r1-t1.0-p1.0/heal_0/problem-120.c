#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    long first;
    long second;
} TuplePair;

static bool max_tuple_product(const TuplePair *pairs, size_t count, long *result)
{
    size_t i;
    long max_product;

    if (pairs == NULL || result == NULL || count == 0U) {
        return false;
    }

    max_product = pairs[0].first * pairs[0].second;

    for (i = 1U; i < count; i++) {
        const long product = pairs[i].first * pairs[i].second;
        if (product > max_product) {
            max_product = product;
        }
    }

    *result = max_product;
    return true;
}

int main(void)
{
    const TuplePair pairs[] = {
        {2L, 5L},
        {8L, 7L},
        {1L, 4L},
        {9L, 10L}
    };
    const size_t count = sizeof(pairs) / sizeof(pairs[0]);
    long max_product = 0L;

    if (max_tuple_product(pairs, count, &max_product)) {
        (void)printf("Maximum product: %ld\n", max_product);
    } else {
        (void)fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}