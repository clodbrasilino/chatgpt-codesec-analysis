#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int max_product_pairs(Tuple *tuples, int size) {
    if (tuples == NULL || size <= 0) {
        return INT_MIN;
    }

    int max_product = INT_MIN;
    int current_product;

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            current_product = tuples[i].first * tuples[i].second * 
                            tuples[j].first * tuples[j].second;
            if (current_product > max_product) {
                max_product = current_product;
            }
        }
    }

    return max_product;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {-1, 5},
        {2, -3},
        {0, 7}
    };
    int size = sizeof(tuples) / sizeof(tuples[0]);

    int result = max_product_pairs(tuples, size);

    if (result != INT_MIN) {
        printf("Maximum product from pairs: %d\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}