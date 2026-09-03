#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} tuple_t;

int max_tuple_pair_product(const tuple_t *tuples, size_t count, long long *result) {
    if (tuples == NULL || result == NULL || count == 0) {
        return -1;
    }

    long long max_product = LLONG_MIN;

    for (size_t i = 0; i < count; ++i) {
        long long product = (long long)tuples[i].first * tuples[i].second;
        if (product > max_product) {
            max_product = product;
        }
    }

    *result = max_product;
    return 0;
}

int main(void) {
    tuple_t tuples[] = {
        {3, 4},
        {-2, 5},
        {-10, -6},
        {1, -7}
    };

    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    long long result = 0;

    if (max_tuple_pair_product(tuples, count, &result) != 0) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}