#include <stdio.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int max_product(Tuple* tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return 0;
    }

    int max = INT_MIN;

    for (size_t i = 0; i < size; ++i) {
        int current_product = tuples[i].first * tuples[i].second;
        if (current_product > max) {
            max = current_product;
        }
    }

    return max;
}

int main() {
    Tuple tuples[] = {
        {2, 3},
        {-5, -5},
        {10, 2},
        {-2, 4}
    };
    
    size_t size = sizeof(tuples) / sizeof(tuples[0]);
    
    int result = max_product(tuples, size);
    
    printf("Max product: %d\n", result);
    
    return 0;
}