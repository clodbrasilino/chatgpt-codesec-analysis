#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int a;
    int b;
} Tuple;

long long find_max_product(const Tuple* tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return LLONG_MIN;
    }

    long long max_product = LLONG_MIN;

    for (size_t i = 0; i < size; i++) {
        long long product = (long long)tuples[i].a * (long long)tuples[i].b;
        if (product > max_product) {
            max_product = product;
        }
    }

    return max_product;
}

int main(void) {
    Tuple tuples[] = {
        {2, 3},
        {-5, -6},
        {4, 8},
        {-10, 2}
    };
    size_t size = sizeof(tuples) / sizeof(tuples[0]);

    long long max_prod = find_max_product(tuples, size);

    if (max_prod != LLONG_MIN) {
        printf("Maximum product: %lld\n", max_prod);
    } else {
        printf("Invalid input or empty list.\n");
    }

    return 0;
}