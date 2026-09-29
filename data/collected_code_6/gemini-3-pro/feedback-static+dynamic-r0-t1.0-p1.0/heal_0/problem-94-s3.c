#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int value;
} Tuple;

Tuple get_min_value_tuple(const Tuple *tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        Tuple empty = {-1, -1};
        return empty;
    }

    Tuple min_tuple = tuples[0];
    for (size_t i = 1; i < size; ++i) {
        if (tuples[i].value < min_tuple.value) {
            min_tuple = tuples[i];
        }
    }

    return min_tuple;
}

int main() {
    Tuple tuples[] = {
        {0, 45},
        {1, 23},
        {2, 67},
        {3, 12},
        {4, 89}
    };
    
    size_t size = sizeof(tuples) / sizeof(tuples[0]);

    Tuple min_tuple = get_min_value_tuple(tuples, size);

    if (min_tuple.index != -1) {
        printf("Index: %d, Minimum Value: %d\n", min_tuple.index, min_tuple.value);
    } else {
        printf("Invalid input or empty array.\n");
    }

    return 0;
}