#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
    int third;
} Tuple;

int max_aggregate(Tuple *tuples, int count) {
    if (tuples == NULL || count <= 0) {
        return INT_MIN;
    }

    int *aggregates = (int *)malloc(count * sizeof(int));
    if (aggregates == NULL) {
        return INT_MIN;
    }

    for (int i = 0; i < count; i++) {
        aggregates[i] = tuples[i].first + tuples[i].second + tuples[i].third;
    }

    int max_val = aggregates[0];
    for (int i = 1; i < count; i++) {
        if (aggregates[i] > max_val) {
            max_val = aggregates[i];
        }
    }

    free(aggregates);
    return max_val;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {1, 1, 1},
        {10, 20, 30}
    };
    int count = sizeof(tuples) / sizeof(tuples[0]);

    int result = max_aggregate(tuples, count);
    if (result != INT_MIN) {
        printf("Maximum aggregate: %d\n", result);
    }
    else {
        printf("Error: Invalid input or memory allocation failure\n");
    }

    return 0;
}