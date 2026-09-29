#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int weight;
} Tuple;

int max_aggregate(const Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return 0;
    }

    int max_sum = 0;

    for (size_t i = 0; i < count; ++i) {
        int current_sum = tuples[i].value * tuples[i].weight;
        if (i == 0 || current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 5},
        {3, 4},
        {0, 20},
        {5, 2}
    };

    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int result = max_aggregate(tuples, count);

    printf("Maximum aggregate: %d\n", result);

    return 0;
}