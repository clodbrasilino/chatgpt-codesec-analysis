#include <stdio.h>
#include <stddef.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

long long max_product_from_tuples(const Tuple *tuples, size_t count) {
    size_t i;
    long long max_product;

    if (tuples == NULL || count == 0) {
        return LLONG_MIN;
    }

    max_product = (long long)tuples[0].first * tuples[0].second;

    for (i = 1; i < count; i++) {
        long long product = (long long)tuples[i].first * tuples[i].second;
        if (product > max_product) {
            max_product = product;
        }
    }

    return max_product;
}

int main(void) {
    Tuple tuples[] = {
        {3, 7},
        {-2, 5},
        {8, 1},
        {-6, -9},
        {0, 42}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    long long max_product = max_product_from_tuples(tuples, count);

    if (max_product != LLONG_MIN) {
        printf("%lld\n", max_product);
    }

    return 0;
}