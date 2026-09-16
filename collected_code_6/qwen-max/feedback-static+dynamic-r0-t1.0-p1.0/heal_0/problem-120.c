#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int maxProductFromTuples(Tuple *tuples, int size) {
    if (size <= 0) return -1;

    int maxProduct = tuples[0].first * tuples[0].second;
    for (int i = 1; i < size; ++i) {
        int product = tuples[i].first * tuples[i].second;
        if (product > maxProduct) {
            maxProduct = product;
        }
    }

    return maxProduct;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    int result = maxProductFromTuples(tuples, size);
    printf("Max Product: %d\n", result);

    return 0;
}