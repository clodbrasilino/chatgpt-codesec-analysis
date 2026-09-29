#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int a;
    int b;
} Tuple;

int min_product_pairs(Tuple *tuples, int size) {
    if (tuples == NULL || size <= 0) {
        return INT_MAX;
    }

    int min_product = INT_MAX;

    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            int product = tuples[i].a * tuples[i].b + tuples[j].a * tuples[j].b;
            if (product < min_product) {
                min_product = product;
            }
        }
    }

    return min_product;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {-1, 5},
        {2, -3}
    };
    int size = sizeof(tuples) / sizeof(tuples[0]);

    int result = min_product_pairs(tuples, size);

    if (result != INT_MAX) {
        printf("Minimum product: %d\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}