#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_max_product(const Tuple *tuples, size_t size, long long *max_product) {
    if (tuples == NULL || max_product == NULL || size == 0) {
        return -1;
    }

    long long current_max = (long long)tuples[0].first * tuples[0].second;

    for (size_t i = 1; i < size; ++i) {
        long long product = (long long)tuples[i].first * tuples[i].second;
        if (product > current_max) {
            current_max = product;
        }
    }

    *max_product = current_max;
    return 0;
}

int main(void) {
    Tuple pairs[] = {
        {3, 5},
        {-4, -8},
        {10, 2},
        {0, 7}
    };
    
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    long long max_product = 0;

    if (find_max_product(pairs, count, &max_product) == 0) {
        printf("%lld\n", max_product);
    } else {
        fprintf(stderr, "Invalid input or empty list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}