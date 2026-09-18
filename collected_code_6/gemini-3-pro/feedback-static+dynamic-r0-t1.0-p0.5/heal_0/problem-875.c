#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_min_difference(Tuple* tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return -1;
    }

    int min_diff = INT_MAX;

    for (size_t i = 0; i < size; i++) {
        int diff = abs(tuples[i].first - tuples[i].second);
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}

int main() {
    Tuple tuples[] = {
        {10, 5},
        {20, 18},
        {30, 25},
        {40, 42}
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