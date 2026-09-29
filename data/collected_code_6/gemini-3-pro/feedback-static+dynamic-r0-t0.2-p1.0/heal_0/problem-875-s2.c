#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int a;
    int b;
} Tuple;

int find_min_difference(Tuple* tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return -1;
    }

    int min_diff = INT_MAX;

    for (size_t i = 0; i < size; ++i) {
        int diff = abs(tuples[i].a - tuples[i].b);
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}

int main(void) {
    Tuple tuples[] = {
        {10, 20},
        {5, 8},
        {100, 101},
        {50, 25}
    };
    size_t size = sizeof(tuples) / sizeof(tuples[0]);

    int min_diff = find_min_difference(tuples, size);

    if (min_diff != -1) {
        printf("Minimum difference: %d\n", min_diff);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}