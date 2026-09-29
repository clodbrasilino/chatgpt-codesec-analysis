#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long first;
    long long second;
} Tuple;

static int max_product_tuple(const Tuple *tuples, size_t count, long long *result)
{
    size_t i;
    long long max_prod;
    long long prod;

    if (tuples == NULL || result == NULL || count == 0U) {
        return -1;
    }

    max_prod = LLONG_MIN;

    for (i = 0U; i < count; i++) {
        prod = tuples[i].first * tuples[i].second;
        if (prod > max_prod) {
            max_prod = prod;
        }
    }

    *result = max_prod;
    return 0;
}

int main(void)
{
    Tuple list[] = {
        {2LL, 7LL},
        {2LL, 6LL},
        {1LL, 8LL},
        {4LL, 9LL}
    };
    size_t count = sizeof(list) / sizeof(list[0]);
    long long result = 0LL;

    if (max_product_tuple(list, count, &result) != 0) {
        (void)fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum product: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}