#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_max_difference(const Tuple *tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return -1;
    }

    int max_diff = abs(tuples[0].first - tuples[0].second);

    for (size_t i = 1; i < size; i++) {
        int current_diff = abs(tuples[i].first - tuples[i].second);
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
    }

    return max_diff;
}

int main(void) {
    Tuple tuples[] = {
        {3, 10},
        {5, 2},
        {8, 15},
        {1, 7}
    };
    size_t size = sizeof(tuples) / sizeof(tuples[0]);

    int result = find_max_difference(tuples, size);

    if (result != -1) {
        printf("Maximum difference: %d\n", result);
    } else {
        printf("Invalid input or empty list.\n");
    }

    return 0;
}