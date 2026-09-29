#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int min_product(const Pair *pairs, size_t count, long long *result)
{
    size_t i;
    long long minimum;

    if (pairs == NULL || result == NULL || count == 0U) {
        return -1;
    }

    minimum = (long long)pairs[0].first * (long long)pairs[0].second;

    for (i = 1U; i < count; i++) {
        const long long product = (long long)pairs[i].first * (long long)pairs[i].second;
        if (product < minimum) {
            minimum = product;
        }
    }

    *result = minimum;
    return 0;
}

int main(void)
{
    Pair data[] = {
        {2, 7},
        {2, 6},
        {1, 8},
        {4, 9}
    };
    size_t count = sizeof(data) / sizeof(data[0]);
    long long result = 0;

    if (min_product(data, count, &result) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum product: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}